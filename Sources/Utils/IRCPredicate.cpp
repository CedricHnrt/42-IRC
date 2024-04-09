#include "../../Includes/IRCPredicate.hpp"
#include <string>

ChannelPredicate::ChannelPredicate(size_t channelId) : channelId(channelId) {}
bool ChannelPredicate::operator () (Channel channel)
{
	return channel.getUniqueId() == this->channelId;
}

bool ChannelPredicate::operator == (size_t channelId)
{
	return channelId == this->channelId;
}