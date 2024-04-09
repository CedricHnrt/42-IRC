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
	std::list<Channel>::iterator iterator = std::find_if(channels.begin(), channels.end(), ChannelPredicate(channelId));
	if (iterator != channels.end())
		return *iterator;
	throw ChannelNotFoundException(channelId, "Channel not found !");
}

void ChannelManager::deleteChannel(size_t channelId)
{
	std::list<Channel>::iterator iterator = std::find_if(channels.begin(), channels.end(),  ChannelPredicate(channelId));
	if (iterator != channels.end())
	{
		channels.erase(iterator);
		return ;
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

