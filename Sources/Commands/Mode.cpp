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

void Mode::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void) channel;
	(void) user;


	std::string channelNew = "";

	if (args[0][0] == '#') {
		channelNew = args[0];
		args.erase(args.begin());
	}

	std::vector<std::vector<std::string > >argV;
	for (std::vector<std::string>::iterator it = args.begin() ; it != args.end() ; ++it)
	{
		size_t i = 0;
		if (it == args.begin())
		{
			std::string res;
			while (it != args.end() && (*(it + 1))[0] != '+' && (*(it + 1))[0] != '-') {
				res += *it;
				res += ' ';
				i++;
				if (i == 5)
					break ;
			}
			std::cout << "res = " << res << std::endl;
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