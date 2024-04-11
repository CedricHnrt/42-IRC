#include "ChannelCacheManager.hpp"
#include <limits>
#include <algorithm>
#include <iostream>
#include <IRCPredicate.hpp>
#include <PrimitivePredicate.hpp>

ChannelCacheManager* ChannelCacheManager::instance = NULL;

ChannelCacheManager::ChannelCacheManager() : channels(std::list<Channel>()), uniqueIdCounter(0){}

void ChannelCacheManager::addToCache(Channel& channel) throw (ChannelCacheException)
{
	if (this->uniqueIdCounter == std::numeric_limits<size_t>::max())
		throw ChannelCacheException(this->uniqueIdCounter, "Maximum number of channels reached !");
	channel.setUniqueId(++this->uniqueIdCounter);
	this->channels.push_back(channel);
}

Channel& ChannelCacheManager::getFromCache(size_t channelId) throw (ChannelCacheException)
{
	std::list<Channel>::iterator iterator = std::find_if(channels.begin(), channels.end(), ChannelPredicate(channelId));
	if (iterator != channels.end())
		return *iterator;
	throw ChannelCacheException(channelId, "Channel not found !");
}

void ChannelCacheManager::deleteFromCache(size_t channelId) throw (ChannelCacheException)
{
	std::list<Channel>::iterator iterator = std::find_if(channels.begin(), channels.end(),  ChannelPredicate(channelId));
	if (iterator != channels.end())
	{
		channels.erase(iterator);
		return ;
	}
	throw ChannelCacheException(channelId, "Channel not found");
}

std::list<Channel> ChannelCacheManager::getCache()
{
	return this->channels;
}

ChannelCacheManager* ChannelCacheManager::getInstance()
{
	return instance == NULL ? instance = new ChannelCacheManager() : instance;
}