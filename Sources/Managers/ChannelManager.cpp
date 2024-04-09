#include "ChannelManager.hpp"
#include "ChannelExceptions.hpp"
#include <limits>
#include <algorithm>
#include <iostream>
#include <IRCPredicate.hpp>
#include <PrimitivePredicate.hpp>

ChannelManager* ChannelManager::instance = NULL;

ChannelManager::ChannelManager()
{
	this->uniqueIdCounter = 0;
}

void ChannelManager::publishChannel(Channel& channel)
{
	if (this->uniqueIdCounter == std::numeric_limits<size_t>::max())
		throw ChannelCreationException("Maximum number of channels reached !");
	channel.setUniqueId(this->uniqueIdCounter++);
	this->channels.push_back(channel);
}

Channel& ChannelManager::getChannel(size_t channelId)
{
	std::list<Channel>::iterator it = channels.begin();
	while (it != channels.end())
	{
		if (it->getUniqueId() == channelId)
			return *it;
		it++;
	}
	throw ChannelNotFoundException(channelId, "Channel not found !");
}

void ChannelManager::deleteChannel(size_t channelId)
{
	std::list<Channel>::iterator it;
	for (it = channels.begin(); it != channels.end(); ++it)
	{
		if (it->getUniqueId() == channelId)
		{
			channels.erase(it);
			return;
		}
	}
	throw ChannelDeletionException(channelId, "Channel not found");
}

std::list<Channel> ChannelManager::getChannels()
{
	return this->channels;
}

ChannelManager* ChannelManager::getInstance()
{
	if (instance == NULL)
		instance = new ChannelManager();
	return instance;
}

