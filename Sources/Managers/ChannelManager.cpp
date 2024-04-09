#include "../../Includes/Channel/ChannelManager.hpp"
#include "../../Includes/Channel/Exceptions/ChannelException.hpp"
#include <limits>
#include <algorithm>
#include <IRCPredicate.hpp>
#include <PrimitivePredicate.hpp>

ChannelManager* ChannelManager::instance = NULL;

void ChannelManager::publishChannel(Channel& channel)
{
	if (this->uniqueIdCounter == std::numeric_limits<size_t>::max())
		throw ChannelCreationException("Maximum number of channels reached !");
	channel.setUniqueId(this->uniqueIdCounter++);
	this->channels.push_back(channel);
}

Channel& ChannelManager::getChannel(size_t channelId)
{
	std::list<Channel>::iterator it;
	for (it = channels.begin(); it != channels.end(); ++it)
	{
		if (it->getUniqueId() == channelId)
			return *it;
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

