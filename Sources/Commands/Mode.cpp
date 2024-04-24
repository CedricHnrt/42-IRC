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

static void printvector(std::vector<std::string> vec)
{
	for (std::vector<std::string >::iterator it = vec.begin() ; it != vec.end() ; ++it)
	{
		std::cout << *it << std::endl;
	}
}

static void printVvector(std::vector<std::vector<std::string> > vec)
{
	size_t i = 0;
	for (std::vector<std::vector<std::string> >::iterator it = vec.begin() ; it != vec.end() ; ++it)
	{
		std::cout << "vector " << i << ":" << std::endl;
		printvector(*it);
		std::cout << std::endl;
		i++;
	}
}

static void handleKeyMode(User *user, std::string channelName, std::vector<std::string> args, int mode)
{
	Channel *targetChannel = ChannelCacheManager::getInstance()->getFromCacheString(channelName);
	ChannelProperties *properties = targetChannel->getProperties();

	if (properties->doesUserHaveMode(user->getUniqueId(), 'o') == false)
	{
		std::cout << "user is not op" << std::endl;
		return ;
	}

	if (mode == PLUS)
	{
		if (args.size() < 2)
		{
			std::cout << "insufficient arguments to add keyword" << std::endl;
			return ;
		}
		std::string keyword = args[1];
		properties->setPassword(keyword);
		properties->setPasswordStatus(true);
		std::cout << "new pass set" << std::endl;
	}
	else
	{
		properties->setPassword("");
		properties->setPasswordStatus(false);
		std::cout << "pass deleted" << std::endl;
	}
}

//static void handleBanMode(User *user, std::string channelName, std::vector<std::string> args, int mode)
//{
//	Channel *targetChannel = ChannelCacheManager::getInstance()->getFromCacheString(channelName);
//	ChannelProperties *properties = targetChannel->getProperties();
//	User *targetUser = UsersCacheManager::getInstance()->getFromNickname(args[1]);
//
//	if (mode == PLUS)
//		properties->addModeToUser(targetUser->getUniqueId(), user->getUniqueId(), 'b');
//	else
//		properties->removeModeToUser(targetUser->getUniqueId(), user->getUniqueId(), 'b');
//}
//
//static void handleTopicMode(User *user, std::string channelName, std::vector<std::string> args, int mode)
//{
//	Channel *targetChannel = ChannelCacheManager::getInstance()->getFromCacheString(channelName);
//	ChannelProperties *properties = targetChannel->getProperties();
//	User *targetUser = UsersCacheManager::getInstance()->getFromNickname(args[1]);
//
//	if (mode == PLUS)
//		properties->addModeToUser(targetUser->getUniqueId(), user->getUniqueId(), 'b');
//	else
//		properties->removeModeToUser(targetUser->getUniqueId(), user->getUniqueId(), 'b');
//}

static void handleUserMode(User *user, std::string channelName, std::vector<std::string> args, int mode, char c)
{
	Channel *targetChannel = ChannelCacheManager::getInstance()->getFromCacheString(channelName);
	ChannelProperties *properties = targetChannel->getProperties();
	User *targetUser = UsersCacheManager::getInstance()->getFromNickname(args[1]);

	if (args.size() < 2){
		std::cout << "insufficient arguments" << std::endl;
	}

	if (mode == PLUS)
		properties->addModeToUser(targetUser->getUniqueId(), user->getUniqueId(), c);
	else
		properties->removeModeToUser(targetUser->getUniqueId(), user->getUniqueId(), c);
}

static void handleAwayMode(User *user, std::string channelName, std::vector<std::string> args, int mode)
{

}

void Mode::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void) channel;
	(void) user;


	std::string channelNew = "";

	if (args[0][0] == '#') {
		channelNew = args[0];
		StringUtils::trim(channelNew, "#");
		args.erase(args.begin());
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

	std::cout << "end of loop, vector size = " << argV.size() << std::endl;
	printVvector(argV);


	std::string userModes = "otvbi";

	for (std::vector<std::vector<std::string> >::iterator it = argV.begin() ; it != argV.end() ; ++it)
	{
		int mode;
		for (std::string::iterator sIt = (*it)[0].begin() ; sIt != (*it)[0].end() ; ++sIt)
		{
			std::cout << "current char: " << *sIt << std::endl;
			if (*sIt == '+')
				mode = PLUS;
			if (*sIt == '-')
				mode = MINUS;
//			if (*sIt == 'a') {
//				try {
//					handleAwayMode(user, channelNew, *it, mode);
//				}
//				catch (std::exception &e) {
//					std::cout << e.what() << std::endl;
//				}
//			}
			if (*sIt == 'k')
			{
				try {
					handleKeyMode(user, channelNew, *it, mode);
				}
				catch (std::exception &e) {
					std::cout << e.what() << std::endl;
				}
			}
			if (userModes.find(*sIt) != std::string::npos) {
				try {
					handleUserMode(user, channelNew, *it, mode, *sIt);
				}
				catch (std::exception &e) {
					std::cout << e.what() << std::endl;
				}
			}

//			if (*sIt == 'b')
//				handleBanMode(user, channelNew, *it, mode);
//			if (*sIt == 't')
//				handleTopicMode(user, channelNew, *it, mode);
		}
	}


//
//	if (!args.size())
//		return ;
//	std::string recipient = args[0];
//	std::string modes;
//	std::string target = "";
//	bool onChannel = false;
//	Channel *targetChannel;
////	User *targetUser;
//	std::string channelName;
//	ChannelProperties *TargetChanProperties;
//
//	std::cout << "got in MODE" << std::endl;
//
//	if (recipient[0] == '#')
//	{
//		if (args.size() < 2)
//			return ;
//		onChannel = true;
//		channelName = recipient;
//		StringUtils::trim(channelName, "#");
//		try {
//			targetChannel = ChannelCacheManager::getInstance()->getFromCacheString(channelName);
//		}
//		catch (std::exception &e) {
//			std::cout << "targetChannel failed" << std::endl;
//			std::cout << e.what() << std::endl;
//			return ;
//		}
//		modes = args[1];
//		if (args.size() > 2)
//			target = args[2];
//	}
//	else
//		modes = args[1];
//
//	std::string prefix;
//	prefix += modes[0];
//	StringUtils::keepOnlyUsefulChar(modes, "tnsmikpovbai");
//	prefix += modes;
//	modes = prefix;
//
//	if (modes[0] == '+')
//	{
//		std::cout << "got in +" << std::endl;
//		StringUtils::trim(modes, "+");
//		TargetChanProperties = targetChannel->getProperties();
//		if (onChannel)
//		{
//			//modifying channel;
//				std::cout << "calling user: " << user->getNickname() << ". his modes: " <<
//				std::cout << "got in target not empty" << std::endl;
//				for (std::string::iterator it = modes.begin() ; it != modes.end() ; ++it)
//				{
//					try {
////						TargetChanProperties->addModeToChannel(user->getUniqueId(), *it);
//						if (*it == 'k')
//						{
//							std::cout << "gotta handle password" << std::endl;
//							TargetChanProperties->setPassword(target);
//							TargetChanProperties->setPasswordStatus(true);
//							return ;
//						}
//						if (*it == 'b')
//						{
//							User *targetUser = UsersCacheManager::getInstance()->getFromNickname(target);
//							TargetChanProperties->addModeToUser(targetUser->getUniqueId(), user->getUniqueId(), *it);
//						}
//						if (*it == 't')
//						{
//							TargetChanProperties->setTopic(user->getUniqueId(), target);
//						}
//					}
//					catch (std::exception &e)
//					{
//						std::cout << "channel mode failed" << std::endl;
//						std::cout << e.what() << std::endl;
//					}
//				}
//			}








//			else
//			{
//				try {
//					targetUser = UsersCacheManager::getInstance()->getFromNickname(target);
//				}
//				catch (std::exception &e)
//				{
//					std::cout << e.what() << std::endl;
//					return;
//				}
//				for (std::string::iterator it = modes.begin() ; it != modes.end() ; ++it)
//				{
//					chanProperties->addModeToUser(targetUser->getUniqueId(), user->getUniqueId(), *it);
//				}
//			}
//		}
//		else
//		{
//			if (modes.find('a') != std::string::npos)
//				chanProperties->addModeToUser(user->getUniqueId(), 0, 'a');
//		}
//	}

}