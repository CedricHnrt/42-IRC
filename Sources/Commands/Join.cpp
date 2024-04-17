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
void Join::execute(User *user, Channel *channel, std::vector<std::string>args)
{
	(void) user;
	(void) channel;

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

	//create a map with key = channelName et value = password
	for (std::vector<std::string>::iterator chanIt = Channels.begin() ; chanIt != Channels.end() ; ++chanIt)
	{
		std::pair<std::string, std::string> result;
		result.first = *chanIt;
		result.second = *passIt;

		ChannelsPasswords.push_back(result);

		passIt++;
	}

	ChannelCacheManager *ChanManager = ChannelCacheManager::getInstance();
	ChannelBuilder *Builder = new ChannelBuilder();

	//chek the channel cache manager, if !exist->add new, else to implement(join existing channel with pword if necessary)
	for (std::vector<std::pair<std::string, std::string> >::iterator it = ChannelsPasswords.begin() ; it != ChannelsPasswords.end() ; ++it)
	{
		if (ChanManager->getFromCacheString(it->first))
		{
			//Channel already exists
		}
		else
		{
			//create new channel
			std::cout << "it->first: " << it->first << std::endl;
			Builder->setName(it->first);
			Builder->setPassword(it->second);
			Builder->setTopic("");
			try {
				ChanManager->addToCache(Builder->build());
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}

	std::list<Channel *> test = ChanManager->getCache();
	std::cout << "front: " << test.front()->getName() << std::endl;

	if (ChanManager->getFromCacheString(Channels.front()))
	{
		std::cout << "channel successfully created" << std::endl;
	}

}
