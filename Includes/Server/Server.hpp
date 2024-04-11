

#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../../Includes/Builders/UserBuilder.hpp"
#include "../../Includes/CacheManager/UsersCacheManager.hpp"


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>

#ifndef PORT
#define PORT 7777
#endif

class Server
{
	private:
		Server();
		Server(const Server &obj);
		Server &operator=(const Server &obj);

		int _socketfd;
		sockaddr_in _serverSocket;
		std::string _password;
		std::vector<struct pollfd> _fds;

		//key = userSocketFd
		std::map<int, UserBuilder> _danglingUsers;
		std::vector <User> _allUsers;

	public:
		Server(char *port, char *password);
		~Server();

		void quit();
		void serverUp();
		bool handleNewClient();
		void handleIncomingRequest(int incomingFD);
		void getNewClientInfos(int incomingFD);
		void handleKnownClient(int incomingFD);

	class SocketFDException : public std::exception
	{
		const char *what() const throw() { return ("Error: Could not create the socket"); }
	};
	class wrongArgumentException : public std::exception
	{
		const char *what() const throw() { return ("Error: Wrong arguments\nUsage: ./ircserv <port> <password>"); }
	};
	class ServerInitializationException : public std::exception
	{
		const char *what() const throw() { return ("Error: Could not initialize the IRC server"); }
	};
	class CommunicationException : public std::exception
	{
		const char *what() const throw() { return ("Error: A problem occurred while communicating with a client"); }
	};



};


#endif
