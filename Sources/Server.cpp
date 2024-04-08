//
// Created by pgouasmi on 4/5/24.
//

#include "Server.hpp"

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

Server::Server(char *port, char *password)
{
	//creation du socket (fd / interface)
	this->_socketfd = socket(AF_INET, SOCK_STREAM, 0);

	std::cout << "socketfd = "<< this->_socketfd << std::endl;

	if (this->_socketfd < 0)
	{
		this->exit();
		throw SocketFDException();
	}
	if (parsePort(std::string(port) ) || parsePassword(std::string(password))) {
		this->exit();
		throw wrongArgumentException();
	}

	this->_password = password;

	/*remplir la struct sockaddr_in
	 * qui contient le duo IP + port*/
	this->_serverSocket.sin_family = AF_INET;
	this->_serverSocket.sin_port = htons(atoi(port));
	std::cout << "sin_port = "<< this->_serverSocket.sin_port << std::endl;
	/* traduit en binaire l'adresse IP */
	inet_pton(AF_INET, "127.0.0.1", &this->_serverSocket.sin_addr);

	/*associer le socket a l'adresse et port dans sockaddr_in*/
	int res = bind(this->_socketfd, reinterpret_cast<sockaddr *>(&(this->_serverSocket)), sizeof(_serverSocket));

	std::cout << res << std::endl;

	/*mettre le socket en ecoute passive*/
	int lis = listen(this->_socketfd, 10);
	std::cout << "lis = " << lis << std::endl;

	/*permet de surveiller un fd (ou socket en l'occurence)
	 * selon des events
	 * */
	pollfd fds;
	fds.fd = this->_socketfd;
	std::cout << fds.fd << std::endl;

	//surveiller entree
	fds.events = POLLIN;
	socklen_t len = sizeof(this->_serverSocket);
	while (1)
	{
		int client_sock = accept(this->_socketfd, reinterpret_cast<sockaddr *>(&(this->_serverSocket)), &len);
		if (client_sock < 0)
		{
			std::cout << "client sock failed" << std::endl;
			this->exit();
		}
		else {
			std::cout << "connection OK" << std::endl;
			char buffer[512];
			size_t size = recv(client_sock, buffer, 512, 0);
			buffer[size] = '\0';
			std::cout << buffer << std::endl;
		}
	}
}


void Server::exit()
{
	close(this->_socketfd);
}

Server::~Server()
{
	close(this->_socketfd);
}
