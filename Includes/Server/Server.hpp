#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include <fcntl.h>
#include <cerrno>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <csignal>

#include "User.hpp"
#include "UserBuilder.hpp"
#include "Configuration.hpp"
#include "StringUtils.hpp"
#include "IrcLogger.hpp"
#include "UsersCacheManager.hpp"
#include "ServerExceptions.hpp"

#define RPL_WELCOME(USERNAME, NICKNAME) (":server 001" + USERNAME + ":Welcome to the Internet Relay Network" + NICKNAME + "\r\n")

class Server
{
	private:
		Server(const Server &obj);
		Server &operator=(const Server &obj);

		int _socketfd;
		sockaddr_in _serverSocket;
		std::string _password;
		std::vector<pollfd> _fds;

		//key = userSocketFd
		std::map<int, UserBuilder> _danglingUsers;
		std::vector <User> _allUsers;

	public:
		Server() throw(ServerInitializationException);
		~Server();

		void serverUp() throw(ServerStartingException);
		bool handleNewClient();
		void handleIncomingRequest(int incomingFD);
		void getNewClientInfos(int incomingFD);
		void handleKnownClient(int incomingFD, std::string buffer);
		void closeOpenedSockets();
		void sigHandler();
};


#endif
