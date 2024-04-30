//
// Created by pgouasmi on 4/23/24.
//

#include "Mode.hpp"

Mode::Mode()
{
	this->_name = "MODE";
	this->_permissionLevel = 1;
	this->_usage = "/mode #canal +b user // /mode your_nickname +a";
	this->_description = "Modifies attributes or permissions for a user or a channel";

	(void)this->_expectedArgs;
}

//static void printvector(std::vector<std::string> vec)
//{
//	for (std::vector<std::string >::iterator it = vec.begin() ; it != vec.end() ; ++it)
//	{
//		std::cout << *it << std::endl;
//	}
//}
//
//static void printVvector(std::vector<std::vector<std::string> > vec)
//{
//	size_t i = 0;
//	for (std::vector<std::vector<std::string> >::iterator it = vec.begin() ; it != vec.end() ; ++it)
//	{
//		std::cout << "vector " << i << ":" << std::endl;
//		printvector(*it);
//		std::cout << std::endl;
//		i++;
//	}
//}


static void handleBanMode(User *user, std::string channelName, std::vector<std::string> args, int mode)
{
	(void)user;

	Channel *targetChannel = ChannelCacheManager::getInstance()->getFromCacheString(channelName);
	ChannelProperties *properties = targetChannel->getProperties();
	User *targetUser = UsersCacheManager::getInstance()->getFromNickname(args[1]);

	if (mode == PLUS)
	{
		if (targetChannel->isUserInChannel(targetUser->getNickname()))
		{
			std::string message = "You've been banned from #" + channelName;
			sendServerReply(targetUser->getUserSocketFd(), RPL_NOTICE(targetUser->getNickname(), targetUser->getUserName(), user->getNickname(), message), -1, DEFAULT);
			properties->addUserToBannedUsers(targetUser->getUniqueId());
		}
	}
	else
	{
		if (properties->isUserBanned(targetUser->getUniqueId())) {
			std::string message = "You've been unbanned from #" + channelName;
			sendServerReply(targetUser->getUserSocketFd(),
							RPL_NOTICE(targetUser->getNickname(), targetUser->getUserName(), user->getNickname(),
									   message), -1, DEFAULT);
			properties->removeUserFromBannedUsers(targetUser->getUniqueId());
		}
	}

}

static void handleKeyMode(User *user, std::string channelName, std::vector<std::string> args, int mode)
{
	Channel *targetChannel = ChannelCacheManager::getInstance()->getFromCacheString(channelName);
	ChannelProperties *properties = targetChannel->getProperties();

	if (mode == PLUS)
	{
		if (args.size() < 2)
		{
			sendServerReply(user->getUserSocketFd(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"), -1, DEFAULT);
			return ;
		}
		std::string keyword = args[1];
		properties->setPassword(keyword);
		properties->setPasswordStatus(true);
		properties->addModeToChannel(user->getUniqueId(), 'k');
		sendServerReply(user->getUserSocketFd(), RPL_CHANNELMODEISWITHKEY(user->getNickname(), channelName, "k", properties->getPassword()), -1, DEFAULT);
		std::cout << "new pass set" << std::endl;
	}
	else if (mode == MINUS)
	{
		properties->setPassword("");
		properties->setPasswordStatus(false);
		sendServerReply(user->getUserSocketFd(), RPL_CHANNELMODEIS(user->getNickname(), channelName, "-k"), -1, DEFAULT);
		std::cout << "pass deleted" << std::endl;
		properties->removeModeToChannel(user->getUniqueId(), 'k');
	}
}

static void handleLimitMode(User *user, std::string channelName, std::vector<std::string> args, int mode)
{
	Channel *targetChannel = ChannelCacheManager::getInstance()->getFromCacheString(channelName);
	ChannelProperties *properties = targetChannel->getProperties();


	if (mode == PLUS)
	{
		if (args.size() < 2)
		{
			sendServerReply(user->getUserSocketFd(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"), -1, DEFAULT);
			return ;
		}
		if (!StringUtils::isOnlyDigits(args[1]))
		{
			sendServerReply(user->getUserSocketFd(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"), -1, DEFAULT);
			std::cout << "limits must be digit" << std::endl;
			return ;
		}

		char *pEnd;
		double newLimit = strtod(args[1].c_str(), &pEnd);
		if (newLimit > INT_MAX)
		{
			std::cout << "limit is too high" << std::endl;
			return ;
		}
		properties->addModeToChannel(user->getUniqueId(), 'l');
		properties->setUserLimit(static_cast<int>(newLimit));
		properties->setUserLimitStatus(true);
	}
	else if (mode == MINUS)
	{
		properties->setUserLimit(-1);
		properties->setUserLimitStatus(false);
		properties->removeModeToChannel(user->getUniqueId(), 'l');
	}
}

static void handleUserMode(User *user, std::string channelName, std::vector<std::string> args, int mode, char c)
{
	Channel *targetChannel = ChannelCacheManager::getInstance()->getFromCacheString(channelName);
	ChannelProperties *properties = targetChannel->getProperties();
	User *targetUser = UsersCacheManager::getInstance()->getFromNickname(args[1]);

	if (args.size() < 2){
		sendServerReply(user->getUserSocketFd(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"), -1, DEFAULT);
		return ;
	}
	if (mode == PLUS)
		properties->addModeToUser(targetUser->getUniqueId(), user->getUniqueId(), c);
	else if (mode == MINUS)
		properties->removeModeToUser(targetUser->getUniqueId(), user->getUniqueId(), c);
	if (c == 'o' && mode == PLUS)
		sendServerReply(targetUser->getUserSocketFd(), RPL_YOUREOPER(targetUser->getNickname()), -1, DEFAULT);
}

static void handleChannelMode(User *user, std::string channelName, std::vector<std::string> args, int mode, char c)
{
	Channel *targetChannel = ChannelCacheManager::getInstance()->getFromCacheString(channelName);
	ChannelProperties *properties = targetChannel->getProperties();

	if (args.size() < 1){
		sendServerReply(user->getUserSocketFd(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"), -1, DEFAULT);
	}

	if (mode == PLUS)
		properties->addModeToChannel(user->getUniqueId(), c);
	else if (mode == MINUS)
		properties->removeModeToChannel(user->getUniqueId(), c);
}

void Mode::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void) channel;
	(void) user;

	std::string channelNew;

	if (args[0][0] != '#') {
		sendServerReply(user->getUserSocketFd(), ERR_NEEDMOREPARAMS(user->getNickname(), this->_name), -1, DEFAULT);
		return;
	}

	channelNew = args[0];
	StringUtils::trim(channelNew, "#");
	args.erase(args.begin());

	Channel *targetChannel = ChannelCacheManager::getInstance()->getFromCacheString(channelNew);
	ChannelProperties *properties = targetChannel->getProperties();


	if (properties->isUserOnChannel(user->getUniqueId()) == false)
	{
		sendServerReply(user->getUserSocketFd(), ERR_NOTONCHANNEL(user->getNickname(), channelNew), -1, DEFAULT);
		return ;
	}

	if (args.size() == 0)
	{
		if (properties->isPasswordSet() == true)
			sendServerReply(user->getUserSocketFd(), RPL_CHANNELMODEISWITHKEY(user->getNickname(), channelNew, properties->getChannelModes(), properties->getPassword()), -1, DEFAULT);
		else
			sendServerReply(user->getUserSocketFd(), RPL_CHANNELMODEIS(user->getNickname(), channelNew, properties->getChannelModes()), -1, DEFAULT);
		return ;
	}

	if (properties->isUserOperator(user->getUniqueId()) == false)
	{
		sendServerReply(user->getUserSocketFd(), ERR_CHANOPRIVSNEEDED(user->getNickname(), channelNew), -1, DEFAULT);
		return ;
	}

	bool New = true;

	std::vector<std::vector<std::string > >argV;
	for (std::vector<std::string>::iterator it = args.begin() ; it != args.end() ; ++it)
	{
		std::string res;
		while (it != args.end()) {
			if (New)
			{
				res += *it;
				res += ' ';
				it++;
				New = false;
			}
			else
			{
				if (((*it)[0] != '+' && (*it)[0] != '-'))
				{
					New = false;
					res += *it;
					res += ' ';
					it++;
					if (it == args.end())
						break;
				}
				else
				{
					New = true;
					break;
				}
			}
		}
		StringUtils::trim(res, " ");
		argV.push_back(StringUtils::split(res, ' '));
		if (it == args.end())
			break ;
		res.clear();
		New = true;
		if ((*it)[0] == '+' || (*it)[0] == '-')
			--it;
	}

	std::string userModes = "ovq";
	std::string channelModes = "ti";

	for (std::vector<std::vector<std::string> >::iterator it = argV.begin() ; it != argV.end() ; ++it)
	{
		int mode = 42;
		for (std::string::iterator sIt = (*it)[0].begin() ; sIt != (*it)[0].end() ; ++sIt)
		{
			if (*sIt == '+')
				mode = PLUS;
			if (*sIt == '-')
				mode = MINUS;
			if (*sIt == 'k')
			{
				try {
					handleKeyMode(user, channelNew, *it, mode);
				}
				catch (std::exception &e) {
					std::cout << e.what() << std::endl;
				}
			}
			if (mode == 42)
				sendServerReply(user->getUserSocketFd(), ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"), -1, DEFAULT);
			else if (*sIt == 'l')
			{
				try {
					handleLimitMode(user, channelNew, *it, mode);
				}
				catch (std::exception &e) {
					std::cout << e.what() << std::endl;
				}
			}
			else if (*sIt == 'b')
			{
				try {
					handleBanMode(user, channelNew, *it, mode);
				}
				catch (std::exception &e) {
					std::cout << e.what() << std::endl;
				}
			}
			else if (userModes.find(*sIt) != std::string::npos) {
				try {
					handleUserMode(user, channelNew, *it, mode, *sIt);
				}
				catch (std::exception &e) {
					std::cout << e.what() << std::endl;
				}
			}
			else if (channelModes.find(*sIt) != std::string::npos) {
				try {
					handleChannelMode(user, channelNew, *it, mode, *sIt);
				}
				catch (std::exception &e) {
					std::cout << e.what() << std::endl;
				}
			}
		}
	}
	targetChannel->nameReplyAll();
}