//
// Created by pgouasmi on 4/29/24.
//

#include "Kick.hpp"

Kick::Kick()
{
	this->_name = "JOIN";
	this->_permissionLevel = 1;
	this->_usage = "/kick #<channel> nickname";
	this->_description = "(+o) Kick a user from a channel";

	this->_expectedArgs.push_back(CHANNEL);
	this->_expectedArgs.push_back(USER);
}

static void kickReplyServer(Channel *channel, User *userToKick, std::string reason)
{
	std::vector<User *> vector = channel->getChannelsUsers();

	for (std::vector<User *>::iterator it = vector.begin() ; it != vector.end() ; ++it) {
		if ((*it) != userToKick)
			sendServerReply((*it)->getUserSocketFd(),
						RPL_KICK(user_id((*it)->getNickname(), (*it)->getUserName()), channel->getName(),
								 userToKick->getNickname(), reason), -1, DEFAULT);
	}
}

void Kick::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void)user;
	(void)channel;

	std::string userNickname = args[1];
	std::string reason = "";
	IrcLogger *logger = IrcLogger::getLogger();
	User *userToKick;
	ChannelProperties *properties = channel->getProperties();

	if (args.size() > 2)
		reason = args[3];

	try {
		userToKick = channel->getUserByNickname(userNickname);
	}
	catch (const UserCacheExceptionString &e)
	{
		logger->log(IrcLogger::ERROR, e.what());
		sendServerReply(user->getUserSocketFd(), ERR_USERNOTINCHANNEL(user->getNickname(), userNickname, channel->getName()), -1, DEFAULT);
		return ;
	}

	if (!properties->isUserOperator(user->getUniqueId()))
	{
		sendServerReply(user->getUserSocketFd(), ERR_CHANOPRIVSNEEDED(user->getNickname(), channel->getName()), -1, DEFAULT);
		return ;
	}

	std::cout << "before" << std::endl;
	channel->removeUserFromChannel(userToKick);
	std::cout << "after remove" << std::endl;
	kickReplyServer(channel, userToKick, reason);
	std::cout << "after reply 1" << std::endl;
	channel->nameReplyAll();
	std::cout << "after reply 2" << std::endl;
}
