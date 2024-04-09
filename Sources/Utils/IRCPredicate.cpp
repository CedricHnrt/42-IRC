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

UserPredicate::UserPredicate(size_t userId) : userId(userId) {}

bool UserPredicate::operator () (User user)
{
	return user.getUniqueId() == this->userId;
}

bool UserPredicate::operator == (size_t userId)
{
	return userId == this->userId;
}