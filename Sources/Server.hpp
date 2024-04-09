

#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include <fcntl.h>


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

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
		int _lastClientFD;

	public:
		Server(char *port, char *password);
		~Server();

		void quit();
		void serverUp();
		bool handleNewClient();
		void handleIncomingRequest(int incomingFD);
		void getNewClientInfos(int incomingFD);

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
