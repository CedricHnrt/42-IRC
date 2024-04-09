#include "ChannelCacheManager.hpp"
#include "../Exceptions/ChannelExceptions.hpp"
#include <limits>
#include <algorithm>
#include <iostream>
#include <IRCPredicate.hpp>
#include <PrimitivePredicate.hpp>

ChannelCacheManager* ChannelCacheManager::instance = NULL;

ChannelCacheManager::ChannelCacheManager() {}

void ChannelCacheManager::addToCache(Channel& channel)
{
	if (this->uniqueIdCounter == std::numeric_limits<size_t>::max())
		throw ChannelCreationException("Maximum number of channels reached !");
	channel.setUniqueId(++this->uniqueIdCounter);
	this->channels.push_back(channel);
}

Channel& ChannelCacheManager::getFromCache(size_t channelId)
{
	std::list<Channel>::iterator iterator = std::find_if(channels.begin(), channels.end(), ChannelPredicate(channelId));
	if (iterator != channels.end())
		return *iterator;
	throw ChannelNotFoundException(channelId, "Channel not found !");
}

void ChannelCacheManager::deleteFromCache(size_t channelId)
{
	std::list<Channel>::iterator iterator = std::find_if(channels.begin(), channels.end(),  ChannelPredicate(channelId));
	if (iterator != channels.end())
	{
		channels.erase(iterator);
		return ;
	}
	throw ChannelDeletionException(channelId, "Channel not found");
}

std::list<Channel> ChannelCacheManager::getCache()
{
	return this->channels;
}

ChannelCacheManager* ChannelCacheManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new ChannelCacheManager();
		instance->uniqueIdCounter = 0;
		instance->channels = std::list<Channel>();
	}
	return instance;
}