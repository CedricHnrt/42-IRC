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
	std::string message = args[1];

//	std::cout << "got in message" << std::endl;
//	std::cout << "recipient: " << recipient << std::endl;
//	std::cout << "message: " << message << std::endl;
	try
	{
		User *Recipient = UsersCacheManager::getInstance()->getFromNickname(recipient);

		//the recipient does not exist
		if (!Recipient)
		{
			sendServerReply(user->getUserSocketFd(), ERR_NOSUCHNICK(user->getNickname(), recipient), RED, BOLDR);
			return ;
		}
		sendServerReply(Recipient->getUserSocketFd(), RPL_PRIVMSG(user->getNickname(), user->getUserName(), recipient, message), BLACK, DEFAULT);
	}
	catch (UserCacheExceptionString &exception)
	{
		IrcLogger *logger = IrcLogger::getLogger();
		logger->log(IrcLogger::ERROR, "An error occurred during message sending !");
		logger->log(IrcLogger::ERROR, exception.what());
		std::string tmp = "Nickname: ";
		logger->log(IrcLogger::ERROR, tmp.append(exception.getValue()));
	}
}

