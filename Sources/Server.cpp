//
// Created by pgouasmi on 4/5/24.
//

#include "Server.hpp"

#define username "bruh"
#define nickname "bruh"

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

Server::Server(char *port, char *password)
{
	/*create the server*/

	//creation du socket (fd / interface)
	this->_socketfd = socket(AF_INET, SOCK_STREAM, 0);

	std::cout << "socketfd = "<< this->_socketfd << std::endl;

	if (this->_socketfd < 0)
	{
		this->quit();
		throw SocketFDException();
	}
	if (parsePort(std::string(port) ) || parsePassword(std::string(password))) {
		this->quit();
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

	int temp = 1;
	if(setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp)) == -1)
	if (fcntl(this->_socketfd, F_SETFL, O_NONBLOCK) == -1)
		std::cout << "fcntl KO" << std::endl;

	/*associer le socket a l'adresse et port dans sockaddr_in*/
	int res = bind(this->_socketfd, reinterpret_cast<sockaddr *>(&(this->_serverSocket)), sizeof(_serverSocket));

	std::cout << res << std::endl;

	/*mettre le socket en ecoute passive*/
	int lis = listen(this->_socketfd, 10);
	std::cout << "lis = " << lis << std::endl;

	/*create the server*/










	/*ADD the SERVER pollfd*/

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



	socklen_t len = sizeof(this->_serverSocket);
	 /*Enregistrer FD de tous les clients, regarder si le fd qui me ping est deja connu
	  * Si oui : recevoir un msg
	  * enregistrer new user
	  * */


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
				{
					//new client
					sockaddr_in newCli;
					pollfd newPoll;

					int client_sock = accept(this->_socketfd, reinterpret_cast<sockaddr *>(&newCli), &len);
					if (client_sock < 0)
					{
						std::cout << "client sock failed" << std::endl;
						this->quit();
						exit(1);
					}
					newPoll.fd = client_sock;
					newPoll.events = POLLIN;
					newPoll.revents = 0;
					std::cout << "client " << client_sock << " connected" << std::endl;
					this->_fds.push_back(newPoll);
					std::string reply = RPL_WELCOME;
					std::cout << reply << std::endl;
					exit(1);
					if (send(client_sock, reply.c_str(), reply.length(), 0) == -1) {
						std::cout << "send failed" << std::endl;
						exit(1);
					}
				}
				else
				{
					//receive data from registered client

//					std::cout << "connection OK" << std::endl;
					char buffer[512];
					size_t size = recv(this->_fds[i].fd, buffer, 512, 0);
					buffer[size] = '\0';
					std::cout << buffer << std::endl;
//					exit(1);
				}
			}
		}



	}
}


void Server::quit()
{
	close(this->_socketfd);
}

Server::~Server()
{
	close(this->_socketfd);
}
