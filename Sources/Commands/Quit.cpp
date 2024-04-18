#include "Quit.hpp"

Quit::Quit()
{
	this->_name = "QUIT";
	this->_description = "Quit the server";
	this->_usage = "/quit <reason>";
	this->_permissionLevel = 0;
	this->_expectedArgs.push_back(STRING);
}

void Quit::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void)channel;
	(void)args;
//	if (!args.empty())
//		sendServerReply(user->getUserSocketFd(), RPL_QUIT(user_id(user->getNickname(), user->getUserName()), args.front()), GREY, ITALIC);
//	else
//		sendServerReply(user->getUserSocketFd(), RPL_QUIT(user_id(user->getNickname(), user->getUserName()), ""), GREY, ITALIC);
	UsersCacheManager::getInstance()->deleteFromCache(user->getUniqueId());
	UsersCacheManager::getInstance()->addToLeftCache(user);
}