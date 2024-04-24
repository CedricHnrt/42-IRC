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
	std::vector<User *>::iterator it = channel->getChannelsUsers().begin();
	while (it != channel->getChannelsUsers().end())
	{
		if ((*it)->getUniqueId() != userId)
			sendServerReply((*it)->getUserSocketFd(), RPL_QUIT(user_id((*it)->getNickname(), (*it)->getUserName()), message), GREY, ITALIC);
		it++;
	}
}

void Quit::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void)channel;
	(void)args;

	std::vector<Channel *>::iterator it = user->getChannelList().begin();
	while (it != user->getChannelList().end())
	{
		Channel *tmp = *it;
		this->sendQuitMessageToChan(tmp, args.front(), user->getUniqueId());
		it++;
	}
	UsersCacheManager::getInstance()->addToLeftCache(user);
	UsersCacheManager::getInstance()->deleteFromCache(user->getUniqueId());
//	if (!args.empty())
//		sendServerReply(user->getUserSocketFd(), RPL_QUIT(user_id(user->getNickname(), user->getUserName()), args.front()), GREY, ITALIC);
//	else
//		sendServerReply(user->getUserSocketFd(), RPL_QUIT(user_id(user->getNickname(), user->getUserName()), ""), GREY, ITALIC);
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