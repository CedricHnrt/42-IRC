//
// Created by pgouasmi on 4/5/24.
//

#include "Server.hpp"

//#define username "bruh"
//#define nickname "bruh"

#define user_id (":" + nickname + "!" + username + "@localhost")

#define RPL_WELCOME (":localhost 001 bruh :Welcome to the Internet Relay Network :bruh!bruh@localhost\r\n")

static bool parsePort(const std::string &port)
{
	if (port.find_first_not_of("0123456789") != std::string::npos)
		return 1;
	const char *temp = port.c_str();
	long nb = strtol(temp, NULL, 10);
	if (nb < 1024 || nb > 49151)
		return 1;
	return 0;
}

static bool parsePassword(const std::string &password)
{
	for (size_t i = 0; i < password.length(); i++)
	{
		//ajouter le :
		if (!isalnum(password[i]))
			return 1;
	}
	return 0;
}

Server::Server(char *port, char *password) {
	/*create the server*/

	//creation du socket (fd / interface)
	this->_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socketfd < 0) {
		this->quit();
		throw SocketFDException();
	}
	if (parsePort(std::string(port)) || parsePassword(std::string(password))) {
		this->quit();
		throw wrongArgumentException();
	}

	this->_password = password;

	/*remplir la struct sockaddr_in
	 * qui contient le duo IP + port*/
	this->_serverSocket.sin_family = AF_INET;
	this->_serverSocket.sin_port = htons(atoi(port));
	/* traduit en binaire l'adresse IP */
	inet_pton(AF_INET, "127.0.0.1", &this->_serverSocket.sin_addr);

	int temp = 1;
	if (setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp)) == -1)
		throw ServerInitializationException();
	if (fcntl(this->_socketfd, F_SETFL, O_NONBLOCK) == -1)
		throw ServerInitializationException();

	/*associer le socket a l'adresse et port dans sockaddr_in*/
	if (bind(this->_socketfd, reinterpret_cast<sockaddr *>(&(this->_serverSocket)), sizeof(_serverSocket)) == -1)
		throw ServerInitializationException();
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

void Server::serverUp()
{
	/*mettre le socket en ecoute passive*/
	if (listen(this->_socketfd, 10) == -1)
		throw ServerInitializationException();
	while (1)
	{
		if (poll(&this->_fds[0], this->_fds.size(), -1) == -1)
			std::cout << "poll error" << std::endl;

		for (size_t i = 0;  i < this->_fds.size(); i++)
		{
//			std::cout << i << std::endl;
			if (this->_fds[i].revents & POLLIN)
			{
				if (this->_fds[i].fd == this->_socketfd)
					this->handleNewClient();
				else
				{
					this->handleIncomingRequest(this->_fds[i].fd);
				}
			}
		}
	}
}

void Server::getNewClientInfos(int incomingFD)
{
	char buffer[512];

	std::cout << "got in new client infos" << std::endl;
	size_t size = recv(incomingFD, buffer, 512, 0);
	buffer[size] = '\0';
	std::cout << buffer << std::endl;

	std::string infos(buffer);

}

void Server::handleIncomingRequest(int incomingFD)
{
	char buffer[512];
	size_t size = recv(incomingFD, buffer, 512, 0);
	buffer[size] = '\0';
	std::cout << buffer << std::endl;
}

bool Server::handleNewClient() {
	sockaddr_in newCli;
	pollfd newPoll;
	socklen_t len = sizeof(this->_serverSocket);


	int client_sock = accept(this->_socketfd, reinterpret_cast<sockaddr *>(&newCli), &len);
	if (client_sock < 0) {
		return false;
	}
	newPoll.fd = client_sock;
	newPoll.events = POLLIN;
	newPoll.revents = 0;

	this->getNewClientInfos(newPoll.fd);

/*RECEIVING FIRST MESSAGE*/

//	char buffer[1024];
//	memset(buffer, 0, 1024);
//	if (recv(newPoll.fd, buffer, 1024, 0) == -1)
//		throw CommunicationException();
//	std::cout << "buffer =" << buffer << std::endl;
//	std::cout << "client " << client_sock << " connected" << std::endl;
//	memset(buffer, 0, 1024);

/*RECEIVING FIRST MESSAGE*/


/*SENDING WELCOME MESSAGE*/

	this->_fds.push_back(newPoll);
	return true;
}


void Server::quit()
{
	for (size_t i = 0; i < this->_fds.size() ; i++)
		close(this->_fds[i].fd);
}

Server::~Server()
{
	close(this->_socketfd);
}
