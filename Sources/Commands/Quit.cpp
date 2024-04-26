#include "Quit.hpp"

Quit::Quit()
{
	this->_name = "QUIT";
	this->_description = "Quit the server";
	this->_usage = "/quit <reason>";
	this->_permissionLevel = 0;
	this->_expectedArgs.push_back(STRING);
}

void Quit::sendQuitMessageToChan(Channel *channel, User *leftUser, const std::string& message) {
	std::vector<User *> userList = channel->getChannelsUsers();
	for (std::vector<User *>::iterator it = userList.begin(); it != userList.end(); it++) {
		if ((*it)->getNickname() != leftUser->getNickname()) {
			sendServerReply((*it)->getUserSocketFd(),
							RPL_QUIT(user_id(leftUser->getNickname(), leftUser->getUserName()), message),
							-1, DEFAULT);
		}
	}
}

void Quit::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void)channel;
	std::vector<Channel *> channelList = user->getChannelList();
	for (std::vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
		this->sendQuitMessageToChan(*it, user, StringUtils::getMessage(args));
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