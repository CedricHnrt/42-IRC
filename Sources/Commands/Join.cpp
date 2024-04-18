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

#include <iostream>
/*
 * [1] Create a vector of pairs channelName/password
 * [2] Iterate through this vector, if the channel does not exist --> [3], else [4]
 *
 * [3] Create a new channel and add it to the channel cache manager
 *
 * [4] try to make the user join an existing channel
 * 		- if the user is already on the channel --> return
 * 		- check if a password is set and compare it to the one given to the client
 * 		*/
void Join::execute(User *user, Channel *channel, std::vector<std::string>args)
{
	(void)user;
	(void)channel;
	std::vector<std::pair<std::string, std::string> > ChannelsPasswords;
	std::vector<std::string> Channels = StringUtils::split(args.front(), ',');
	std::vector<std::string> Passwords;

	if (args.size() > 1) {
		Passwords = StringUtils::split(args[1], ',');
		for (size_t i = Passwords.size() ; i < Channels.size() ; i++)
			Passwords.push_back("");
	}
	else
	{
		for (size_t i = 0 ; i < Channels.size() ; i++)
			Passwords.push_back("");
	}

	std::vector<std::string>::iterator passIt = Passwords.begin();

	//[1]
	for (std::vector<std::string>::iterator chanIt = Channels.begin() ; chanIt != Channels.end() ; ++chanIt)
	{
		std::pair<std::string, std::string> result;
		result.first = *chanIt;
		result.second = *passIt;

		ChannelsPasswords.push_back(result);

		passIt++;
	}
	//[1]

	ChannelCacheManager *ChanManager = ChannelCacheManager::getInstance();
	ChannelBuilder *Builder = new ChannelBuilder();

	//[2]
	//chek the channel cache manager, if !exist->add new, else to implement(join existing channel with pword if necessary)
	for (std::vector<std::pair<std::string, std::string> >::iterator it = ChannelsPasswords.begin() ; it != ChannelsPasswords.end() ; ++it)
	{
		if (ChanManager->getFromCacheString(it->first))
		{
			//[4]
			Channel *existingChannel = ChanManager->getFromCacheString(it->first);
			//Channel already exists
			std::cout << "channel already exists" << std::endl;

			//is this user already on channel ?
			if (existingChannel->getUserByName(user->getUserName())) {
				std::cout << "user is already in channel" << std::endl;
				sendServerReply(user->getUserSocketFd(),
								ERR_USERONCHANNEL(user->getUserName(), user->getNickname(), existingChannel->getName()),
								RED, DEFAULT);
				return;
			}
			if (it->second != existingChannel->getPassword()) {
				sendServerReply(user->getUserSocketFd(),
								ERR_BADCHANNELKEY(user->getNickname(), existingChannel->getName()), RED, BOLDR);
				return;
			}
			//[4]
		}
		else
		{
			//[3]
			//create new channel
			Builder->setName(it->first);
			Builder->setPassword(it->second);
			Builder->setTopic("");
			try {
				Channel *newChannel = Builder->build();
				newChannel->addUserToChannel(user);
				std::cout << "channel's name: " << newChannel->getName() << std::endl;
				ChanManager->addToCache(newChannel);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				return ;
			}
			//[3]
		}
	}
	//[2]
	sendServerReply(user->getUserSocketFd(), RPL_TOPIC(user->getNickname(), ChanManager->getCache().front()->getName(), ChanManager->getCache().back()->getTopic()), GREEN, BOLDR);
}
