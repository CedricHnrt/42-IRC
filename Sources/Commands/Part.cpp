#include "Part.hpp"


Part::Part()
{
	this->_name = "PART";
	this->_description = "Part a channel";
	this->_usage = "/part <#channel>";
	this->_permissionLevel = 0;
	this->_expectedArgs.push_back(STRING);
}

void Part::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void)channel;
	(void)user;
	(void)args;
//	ChannelCacheManager::getInstance()->getFromCache(channel->getUniqueId()).;
//	UsersCacheManager::getInstance()->deleteFromCache(user->getUniqueId());
}