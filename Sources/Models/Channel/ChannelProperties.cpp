#include "ChannelProperties.hpp"

std::list<size_t> ChannelProperties::getUsersInChannel()
{
	return this->usersInChannel;
}

std::list<size_t> ChannelProperties::getMutedUsers()
{
	return this->mutedUsers;
}

std::list<size_t> ChannelProperties::getBannedUsers()
{
	return this->bannedUsers;
}

std::list<size_t> ChannelProperties::getInvited()
{
	return this->invited;
}

std::list<size_t> ChannelProperties::getOperators()
{
	return this->operators;
}