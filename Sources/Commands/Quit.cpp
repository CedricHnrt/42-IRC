#include "Quit.hpp"

Quit::Quit()
{
	this->_name = "QUIT";
	this->_description = "Quit the server";
	this->_usage = "/quit <reason>";
	this->_permissionLevel = 0;
	this->_expectedArgs.push_back(STRING);
}

void Quit::sendQuitMessageToChan(Channel *channel, std::string message, size_t userId) {
	std::vector<User *> userList = channel->getChannelsUsers();
	for (std::vector<User *>::iterator it = userList.begin(); it != userList.end(); it++) {
		if ((*it)->getUniqueId() != userId)
			sendServerReply((*it)->getUserSocketFd(),
							RPL_QUIT(user_id((*it)->getNickname(), (*it)->getUserName()), message),
							GREY, ITALIC);
	}
}

void Quit::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void)channel;
	(void)args;

	std::vector<Channel *> channelList = user->getChannelList();
	for (std::vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
		if (args.size() > 1)
			this->sendQuitMessageToChan(*it, args.front(), user->getUniqueId());
		else
			this->sendQuitMessageToChan(*it, "", user->getUniqueId());
		(*it)->removeUserFromChannel(user);
	}
	try
	{
		UsersCacheManager::getInstance()->deleteFromCache(user->getUniqueId());
		UsersCacheManager::getInstance()->addToLeftCache(user);
	}
	catch (UserCacheException &exception)
	{
		IrcLogger::getLogger()->log(IrcLogger::ERROR, "An error occurred during user quit command !");
		IrcLogger::getLogger()->log(IrcLogger::ERROR, exception.what());
	}
}