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

	for (std::vector<std::string>::iterator chanIt = Channels.begin() ; chanIt != Channels.end() ; ++chanIt)
	{
		std::pair<std::string, std::string> result;
		result.first = *chanIt;
		result.second = *passIt;

		ChannelsPasswords.push_back(result);

		passIt++;
	}

	ChannelCacheManager *ChanManager = ChannelCacheManager::getInstance();
	ChannelBuilder Builder;

	for (std::vector<std::pair<std::string, std::string> >::iterator it = ChannelsPasswords.begin() ; it != ChannelsPasswords.end() ; ++it)
	{
		if (ChanManager->getFromCacheString(it->first))
		{
			//Channel already exists
		}
		else
		{
			Builder.setName(it->first);
			Builder.setPassword("");
			Builder.setTopic("");
			ChanManager->addToCache(Builder.build());
		}
	}

	std::list<Channel> test = ChanManager->getCache();
	std::cout << "front: " << test.front().getName() << std::endl;

	if (ChanManager->getFromCacheString(Channels.front()))
	{
		std::cout << "channel successfully created" << std::endl;
	}

}
