//
// Created by pgoua on 08/05/2024.
//

#include "../Includes/Bot.hpp"
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
//#include "../../Includes/User/User.hpp"
//#include "../../Includes/CacheManager/UsersCacheManager.hpp"


static std::vector<std::string> split(const std::string &input, int c)
{
	std::vector<std::string> result;

	if (input.empty())
		return result;
	std::string trimmed = input;

	if (input.find(c) == std::string::npos)
	{
		result.push_back(input);
		return result;
	}

	size_t i = input.find(c);
	size_t j = 0;
	std::string line;

	while (input[i])
	{
		i = input.find(c, j);
		if (i == std::string::npos)
		{
			std::string subbed = input.substr(j, input.size() - j);
			result.push_back(subbed);
			break;
		}
		line = input.substr(j, i - j);
		i++;
		j = i;
		result.push_back(line);
		line.clear();
	}
	return result;
}

Bot::Bot(char *port, char *password) throw (BotBuildException)
{
	char *pEnd;
	double portValue = strtod(port, &pEnd);

	if (strlen(pEnd) != 0)
		throw (BotBuildException("Port must be digits only"));
	if (portValue < 1024 || portValue > 49151)
		throw (BotBuildException("Impossible port provided"));
	this->_port = static_cast<int>(portValue);

	this->_password = password;

	int	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1)
		throw (BotBuildException("Error on socket creation"));

	memset(&this->_serverAddress, 0, sizeof(this->_serverAddress));
	this->_serverAddress.sin_family = AF_INET;
	this->_serverAddress.sin_addr.s_addr = INADDR_ANY;
	this->_serverAddress.sin_port = htons(this->_port);

    this->_botPollFd.events = POLLIN;
    this->_botPollFd.fd = clientSocket;
}

void Bot::botConnect() throw(BotBuildException)
{
	if (connect(this->_botPollFd.fd, (struct sockaddr*)&this->_serverAddress, sizeof(this->_serverAddress)) == -1) {
		throw (BotBuildException("Error: connect() failed"));
	}
	std::string message = "CAP LS 302\nPASS " + this->_password + "\nNICK IRCHEH_BOT\nUSER IRCHEH_BOT 0 * :realname\r\n";
    if (send(this->_botPollFd.fd, message.c_str(), message.length(), 0) == -1)
		throw (BotBuildException("Error: send failed"));
	std::cout << "so far so good" << std::endl;
}

static bool isRequestCorrect(const std::vector<std::string> &request)
{
	if (request.size() != 4 || request[1] != "PRIVMSG" || request[0][0] != ':' || request[3][0] != ':')
		return false;
	return true;
}

void Bot::handleRequest(const std::string &request)
{
	std::vector<std::string> requestVector = split(request, ' ');

	std::cout << "vector size: " << requestVector.size() << std::endl;

	if (isRequestCorrect(requestVector)) {
		std::string targetNick = requestVector[0].substr(1, requestVector[0].find('!', 1) - 1);
		std::cout << "nick: " << targetNick << std::endl;
//		User *Target = UsersCacheManager::getInstance()->getFromNickname(targetNick);
		std::string message = "PRIVMSG ";
		message += targetNick;
		message += " :nique ta mere\r\n";

		std::cout << "message sent: " << message << std::endl;

//		(send(Target->getUserSocketFd(), message.c_str(), 512, 0) == -1)

		if (send(this->_botPollFd.fd, message.c_str(), 512, 0) == -1)
			std::cout << "err on send" << std::endl;
	}
	else {
		throw BotRunException("Error: Incorrect request");
	}
	return;
}

void Bot::botUp() throw(BotBuildException)
{
	while (1)
	{
		if (poll(&this->_botPollFd, 1, -1) == -1) {
			std::cout << "err on poll" << std::endl;
		}
		else if (this->_botPollFd.revents & POLLIN)
		{
			char buffer[512];
			int size = recv(this->_botPollFd.fd, &buffer, 510, 0);
			if (size == -1)
				std::cout << "err on recv" << std::endl;
			if (size == 0)
			{
				close(this->_botPollFd.fd);
				std::cout << "connection closed" << std::endl;
				return ;
			}
			else {
				std::string request = buffer;
				memset(buffer, 0, size);
				std::cout << "received buffer: " << request << std::endl;
				try {
					this->handleRequest(request);
				}
				catch (std::exception &e)
				{
					std::cout << e.what() << std::endl;
				}
			}

		}

	}
}