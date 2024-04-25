#include "Part.hpp"

Part::Part()
{
	this->_name = "PART";
	this->_description = "Part a channel";
	this->_usage = "/part <#channel> <reason>";
	this->_permissionLevel = 0;
	this->_expectedArgs.push_back(STRING);
}

void Part::sendPartMessageToChan(User *user, Channel *channel, const std::string& reason)
{
	std::vector<User *> userList = channel->getChannelsUsers();
	for (std::vector<User *>::iterator it = userList.begin(); it != userList.end(); it++)
	{
		if (*it != user) {
			sendServerReply((*it)->getUserSocketFd(),RPL_PART(user_id(user->getNickname(), user->getUserName()), channel->getName(), reason),-1, DEFAULT);
		}
	}
}

void Part::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	try {
		channel = ChannelCacheManager::getInstance()->getFromCacheString(args.front().substr(1));
		args.erase(args.begin());
		std::string reason = StringUtils::getMessage(args);
		reason.pop_back();
		sendPartMessageToChan(user, channel, reason);
		channel->removeUserFromChannel(user);
	}
	catch (ChannelCacheException &exception)
	{
		IrcLogger *logger = IrcLogger::getLogger();
		logger->log(IrcLogger::ERROR, exception.what());
	}
}