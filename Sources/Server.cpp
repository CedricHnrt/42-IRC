//
// Created by pgouasmi on 4/5/24.
//

#include "Server.hpp"

static bool parsePort(const std::string &port)
{
	if (port.find_first_not_of("0123456789") != std::string::npos)
		return 1;
	long nb = stol(port, 0, 10);
	if (nb < 1024 || nb > 49151)
		return 1;
	return 0;
}

static bool parsePassword(const std::string &password)
{
	for (size_t i = 0; i < password.length(); i++)
	{
		if (!isascii(password[i]) || isblank(password[i]))
		{
			//throw
			return 1;
		}
	}
	return 0;
}

Server::Server(char *port, char *password)
{
	this->_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "socketfd = "<< this->_socketfd << std::endl;
	if (this->_socketfd < 0)
	{
		//throw
		exit(1);
	}
	if (parsePort(std::string(port) )|| parsePassword(std::string(password)))
	{
		//throw
		exit(1);
	}
	this->_password = password;
	this->_serverSocket.sin_family = AF_INET;
	this->_serverSocket.sin_port = htons(atoi(port));
	std::cout << "sin_port = "<< this->_serverSocket.sin_port << std::endl;
	inet_pton(AF_INET, "127.0.0.1", &this->_serverSocket.sin_addr);
	int res = bind(this->_socketfd, reinterpret_cast<sockaddr *>(&(this->_serverSocket)), sizeof(_serverSocket));

	std::cout << res << std::endl;
}

Server::~Server()
{

}
