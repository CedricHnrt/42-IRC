#include "../../Includes/IRCPredicate.hpp"
#include <iostream>
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

UserPredicateFD::UserPredicateFD(int fd) : socketFD(fd) {}

bool UserPredicateFD::operator () (User user)
{
	return user.getUserSocketId() == this->socketFD;
}

bool UserPredicateFD::operator == (int userId)
{
	std::cout << "fd: " << this->socketFD << std::endl;
	return userId == this->socketFD;
}