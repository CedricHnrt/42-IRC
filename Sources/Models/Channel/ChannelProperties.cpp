#include "../../../Includes/Channel/Channel.hpp"
#include "../../../Includes/Channel/ChannelProperties.hpp"
#include <algorithm>


bool ChannelProperties::containsChannel(std::list<size_t> list, Channel &target)
{
	return std::find(list.begin(), list.end(), target.getUniqueId()) != list.end();;
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
	list.remove_if(target.getUniqueId());
	return true;
}

