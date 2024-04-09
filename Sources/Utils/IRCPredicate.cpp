#include "../../Includes/IRCPredicate.hpp"
#include <string>

ChannelPredicate::ChannelPredicate(const Channel& v) : target(v) {}
bool ChannelPredicate::operator () (const Channel& channel)
{
	return channel.getName() == target.getName() && channel.getUniqueId() == target.getUniqueId();
}

bool ChannelPredicate::operator == (const Channel& channel)
{
	return channel.getName() == target.getName() && channel.getUniqueId() == target.getUniqueId();
}