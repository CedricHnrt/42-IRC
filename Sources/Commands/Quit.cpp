#include "Quit.hpp"

Quit::Quit()
{
	this->_name = "QUIT";
	this->_description = "Quit the server";
	this->_usage = "/quit <reason>";
	this->_permissionLevel = 0;
	this->_expectedArgs.push_back(STRING);
}

static std::string getMessage(std::vector<std::string>& args)
{
	std::string message;
	for (std::vector<std::string>::iterator itMsg = args.begin(); itMsg != args.end(); itMsg++)
	{
		if (itMsg == args.begin())
			*itMsg = (*itMsg).substr(1);
		message += *itMsg + " ";
	}
	return message;
}

void Quit::sendQuitMessageToChan(Channel *channel, User *leftUser, std::vector<std::string> args) {
	std::vector<User *> userList = channel->getChannelsUsers();
	std::string message = getMessage(args);
	for (std::vector<User *>::iterator it = userList.begin(); it != userList.end(); it++) {
		sendServerReply((*it)->getUserSocketFd(),
						RPL_QUIT(user_id(leftUser->getNickname(), leftUser->getUserName()), message),
						-1, DEFAULT);
	}
}

void Quit::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void)channel;
	(void)args;

	std::vector<Channel *> channelList = user->getChannelList();
	for (std::vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
		this->sendQuitMessageToChan(*it, user, args);
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