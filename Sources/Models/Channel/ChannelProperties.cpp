#include "Channel.hpp"
#include "ChannelProperties.hpp"
#include <algorithm>
#include <PrimitivePredicate.hpp>

bool ChannelProperties::containsChannel(std::list<size_t> list, Channel &target)
{
	return std::find_if(list.begin(), list.end(), SizeTPredicate(target.getUniqueId())) != list.end();;
}

bool ChannelProperties::addChannelToList(std::list<size_t> list, Channel &target)
{
	if (containsChannel(list, target))
		return false;
	list.push_back(target.getUniqueId());
	return true;
}

bool ChannelProperties::removeChannelFromList(std::list<size_t> list, Channel &target)
{
	if (!containsChannel(list, target))
		return false;
	list.remove_if(SizeTPredicate(target.getUniqueId()));
	return true;
}

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