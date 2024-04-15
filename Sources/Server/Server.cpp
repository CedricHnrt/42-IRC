//
// Created by pgouasmi on 4/5/24.
//
#include "Server.hpp"

#include <cmath>

static int parsePort(const std::string &port)
{
	if (port.find_first_not_of("0123456789") != std::string::npos)
		return -1;
	const char *temp = port.c_str();
	errno = 0;
	size_t portValue = strtol(temp, NULL, 10);
	if (errno != 0)
		return -1;
	if (portValue < 1024 || portValue > 49151)
		return -1;
	return static_cast<int>(portValue);
}

static bool parsePassword(const std::string &password)
{
	return password.length() <= 510 && !StringUtils::isAlphaNumeric(password);
}

Server::Server() throw(ServerInitializationException)
{
	this->version = "3";
	/* grab the port and password from the configuration */
	ConfigurationSection *section = Configuration::getInstance()->getSection("SERVER");
	std::string portStr = section->getStringValue("port", "25565");
	std::string passwordStr = section->getStringValue("password", "password");

	/*create the server*/

	//creation du socket (fd / interface)
	this->_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	int port = parsePort(portStr);

	if (this->_socketfd < 0)
		throw ServerInitializationException("Socket creation failed.");
	if (port == -1)
		throw ServerInitializationException("Port is invalid. It must be a number between 1024 and 49151.");
	if (parsePassword(passwordStr))
		throw ServerInitializationException("Password is invalid. It must be alphanumeric and less than 510 characters.");

	this->_password = passwordStr;

	/*remplir la struct sockaddr_in
	 * qui contient le duo IP + port*/
	this->_serverSocket.sin_family = AF_INET;
	this->_serverSocket.sin_port = htons(port);
	/* traduit en binaire l'adresse IP */
	inet_pton(AF_INET, "127.0.0.1", &this->_serverSocket.sin_addr);

	int temp = 1;
	if (setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp)) == -1)
		throw ServerInitializationException("setsockopt failed");
	if (fcntl(this->_socketfd, F_SETFL, 0) == -1)
		throw ServerInitializationException("fcntl failed");

	/*associer le socket a l'adresse et port dans sockaddr_in*/
	if (bind(this->_socketfd, reinterpret_cast<sockaddr *>(&(this->_serverSocket)), sizeof(_serverSocket)) == -1)
		throw ServerInitializationException("Unable to bind the socket to the address and port, maybe the port is already in use ?");
	/*permet de surveiller un fd (ou socket en l'occurence)
	 * selon des events
	 * */
	pollfd serverPoll;
	serverPoll.fd = this->_socketfd;
	//surveiller entree
	serverPoll.events = POLLIN;
	serverPoll.revents = 0;
	this->_fds.push_back(serverPoll);

	/*ADD the SERVER pollfd*/
}

void Server::serverUp() throw (ServerStartingException)
{
	/*mettre le socket en ecoute passive*/
	if (listen(this->_socketfd, 10) == -1)
		throw ServerStartingException("listen failed");

	IrcLogger *logger =IrcLogger::getLogger();
	logger->log(IrcLogger::INFO, "Server is up !");
	while (true)
	{
		if (poll(&this->_fds[0], this->_fds.size(), -1) == -1)
			throw ServerStartingException("poll failed");

		for (size_t i = 0; i < this->_fds.size(); i++)
		{
			if (this->_fds[i].revents & POLLIN)
			{
				if (this->_fds[i].fd == this->_socketfd)
					this->handleNewClient();
				else
					this->handleIncomingRequest(this->_fds[i].fd);
			}
		}
	}
}

void Server::handleKnownClient(int incomingFD, std::string buffer)
{
	IrcLogger::getLogger()->log(IrcLogger::INFO, "In Known client");
	IrcLogger::getLogger()->log(IrcLogger::INFO, "New message : " + buffer);
	IrcLogger::getLogger()->log(IrcLogger::INFO, "NickName : " + UsersCacheManager::getInstance()->getFromCacheSocketFD(incomingFD).getNickname());
}

void Server::handleIncomingRequest(int incomingFD)
{
	char buffer[512];

	size_t size = recv(incomingFD, buffer, 512, 0);
	buffer[size] = '\0';
	std::map<int, UserBuilder>::iterator it = this->_danglingUsers.find(incomingFD);
	if (it == this->_danglingUsers.end())
	{
		this->handleKnownClient(incomingFD, buffer);
		return;
	}
	try
	{
		this->_danglingUsers.at(incomingFD).fillBuffer(std::string(buffer), incomingFD);
		if (this->_danglingUsers.at(incomingFD).isBuilderComplete())
		{
//			UsersCacheManager::getInstance()->addToCache(this->_danglingUsers.at(incomingFD).build());

			UsersCacheManager * UManager = UsersCacheManager::getInstance();

			UManager->addToCache(this->_danglingUsers.at(incomingFD).build());

			this->_danglingUsers.erase(incomingFD);

			User CurrentUser = UManager->getFromCacheSocketFD(incomingFD);

			sendServerReply(incomingFD, RPL_WELCOME(user_id(CurrentUser.getNickname(), CurrentUser.getUserName()), CurrentUser.getUserName()), RED, BOLDR);
			ConfigurationSection *section = Configuration::getInstance()->getSection("SERVER");
			if (section == NULL)
				return;
			sendServerReply(incomingFD, RPL_YOURHOST(CurrentUser.getNickname(), section->getStringValue("servername", "IRCHEH"), section->getStringValue("version", "3")), RED, BOLDR);
			sendServerReply(incomingFD, RPL_CREATED(CurrentUser.getNickname(), IrcLogger::getCurrentTime()), CYAN, BOLDR);
//			sendServerReply(incomingFD, RPL_MYINFO(CurrentUser.getNickname(), section->getStringValue("servername"), section->getStringValue("version"), "io", "kost", "k"), RED, BOLDR);
//			sendServerReply(incomingFD, RPL_ISUPPORT(CurrentUser.getNickname(), "CHANNELLEN=32 NICKLEN=9 TOPICLEN=307"), RED, BOLDR);


		}
	}
	catch (UserBuildException &exception)
	{
		IrcLogger *logger = IrcLogger::getLogger();
		logger->log(IrcLogger::ERROR, "An error occurred during user building !");
		logger->log(IrcLogger::ERROR, exception.what());
		this->_danglingUsers.erase(incomingFD);
	}
}

bool Server::handleNewClient()
{
	sockaddr_in newCli;
	pollfd newPoll;
	socklen_t len = sizeof(this->_serverSocket);

	int client_sock = accept(this->_socketfd, reinterpret_cast<sockaddr *>(&newCli), &len);
	if (client_sock < 0)
		return false;

	newPoll.fd = client_sock;
	newPoll.events = POLLIN;
	newPoll.revents = 0;

	UserBuilder newClient;
	this->_danglingUsers[newPoll.fd] = newClient;
	this->_fds.push_back(newPoll);
	return true;
}

void Server::closeOpenedSockets()
{
	for (size_t i = 0; i < this->_fds.size(); i++)
		close(this->_fds[i].fd);
}

Server::~Server()
{
	close(this->_socketfd);
}
