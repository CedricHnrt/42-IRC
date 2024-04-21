//
// Created by pgoua on 21/04/2024.
//

#include "Who.hpp"

Who::Who()
{
	this->_name = "WHO";
	this->_description = "Displays all users in a channel";
	this->_permissionLevel = 0;
	this->_usage = "/who #<channel>";

	this->_expectedArgs.push_back(CHANNEL);
}

#include <iostream>
void Who::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void) channel;

	std::cout << "got in who" << std::endl;
	std::string ChannelName = args.front();
	if (ChannelName[0] != '#')
	{
		sendServerReply(user->getUserSocketFd(), ERR_ARG(user->getUserName(), this->_name, this->_usage), -1, DEFAULT);
		return ;
	}
	StringUtils::trim(ChannelName, "#");

	Channel *currentChannel;

	try {
		currentChannel = ChannelCacheManager::getInstance()->getFromCacheString(ChannelName);
		currentChannel->getUserByName(user->getUserName());
		std::vector<User *> userList = currentChannel->getChannelsUsers();

		std::cout << "nb of users in chan: " << userList.size() << std::endl;

		for (std::vector<User *>::iterator it = userList.begin() ; it != userList.end() ; ++it)
		{
			sendServerReply(user->getUserSocketFd(), RPL_WHOREPLY(ChannelName, user->getUserName(), (*it)->getUserName()), -1, DEFAULT);
		}
	}
	catch (ChannelCacheException &e)
	{
		IrcLogger *logger = IrcLogger::getLogger();
		logger->log(IrcLogger::ERROR, e.what());
		return ;
	}
}
