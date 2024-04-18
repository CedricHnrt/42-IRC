//
// Created by pgouasmi on 4/18/24.
//

#include "Message.hpp"

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

//	if (User)

	std::cout << "got in message" << std::endl;
}

