//
// Created by pgouasmi on 4/16/24.
//

#include "Join.hpp"

Join::Join()
{
	this->_name = "JOIN";
	this->_permissionLevel = 0;
	this->_usage = "/join #<channel> <password>";
	this->_description = "Used to join an existing channel, or create a new one if no channel corresponds to the given channel name.";

	this->_expectedArgs.push_back(STRING);
}


void Join::execute(User *user, Channel *channel, std::vector<std::string>args)
{
	(void) user;
	(void) channel;
	(void) args;
	//args[0] = chan1, chan1
	//faire split + formattage selin commande ici
}
