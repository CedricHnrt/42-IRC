//
// Created by pgouasmi on 4/18/24.
//

#include "Message.hpp"
#include "IrcLogger.hpp"

Message::Message()
{
	this->_name = "PRIVMSG";
	this->_permissionLevel = 0;
	this->_usage = "/msg <recipient> <message>";
	this->_description = "Sends a private message to a chosen user.";

	this->_expectedArgs.push_back(USER);
	this->_expectedArgs.push_back(STRING);
}

void Message::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void)user;
	(void)channel;
	(void)args;

	std::string recipient = args.front();
	args.erase(args.begin());

	std::string message;

	for (std::vector<std::string>::iterator it = args.begin() ; it != args.end() ; ++it)
	{
		message += *it;
		message += " ";
	}
	StringUtils::trim(message, " ");

//	std::cout << "message: " << message << std::endl;

//	for (std::vector<std::string>::iterator it = args.begin() ; it != args.end() ; ++it)
//	{
//		std::cout << *it << std::endl;
//	}


//	std::cout << "got in message" << std::endl;
//	std::cout << "recipient: " << recipient << std::endl;
//	std::cout << "message: " << message << std::endl;

	if (recipient[0] == '#') //msg on a channel
	{
		std::cout << "message sent on a server" << std::endl;

		StringUtils::trim(recipient, "#");

		Channel *currentChannel = ChannelCacheManager::getInstance()->getFromCacheString(recipient);
		std::vector<User *> usersInChannel = currentChannel->getChannelsUsers();

		std::cout << "Users on channel: " << usersInChannel.size() << std::endl;

		for (std::vector<User *>::iterator it = usersInChannel.begin() ; it != usersInChannel.end(); ++it) {
			if ((*it)->getUserName() != user->getUserName())
				sendServerReply((*it)->getUserSocketFd(), RPL_PRIVMSG(user->getNickname(), user->getUserName(), args[0], message), -1, DEFAULT);
//				send((*it)->getUserSocketFd(), ((":" + user->getUserName() + " PRIVMSG" + currentChannel->getName() + " :" + message + "\r\n").c_str()), 100, 0);
		}
	}
	else //private message
	{
		try {
			User *Recipient = UsersCacheManager::getInstance()->getFromNickname(recipient);

			sendServerReply(Recipient->getUserSocketFd(),
							RPL_PRIVMSG(user->getNickname(), user->getUserName(), recipient, message), -1, DEFAULT);
		}
		catch (UserCacheExceptionString &exception) {
			sendServerReply(user->getUserSocketFd(), ERR_NOSUCHNICK(user->getUserName(), recipient), RED, BOLDR);
			IrcLogger *logger = IrcLogger::getLogger();
			logger->log(IrcLogger::ERROR, "An error occurred during message sending !");
			logger->log(IrcLogger::ERROR, exception.what());
			std::string tmp = "Nickname: ";
			logger->log(IrcLogger::ERROR, tmp.append(exception.getValue()));
		}
	}
}

