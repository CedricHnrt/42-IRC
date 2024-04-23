#include "Channel.hpp"
#include "ChannelProperties.hpp"

#include "User.hpp"

Channel::Channel() {}

std::string Channel::getName() const
{
	return this->name;
}

std::string Channel::getTopic() const
{
	return this->topic;
}

std::string Channel::getPassword() const
{
	return this->password;
}

size_t Channel::getUniqueId() const
{
	return this->uniqueId;
}

ChannelProperties &Channel::getProperties()
{
	return this->properties;
}

void Channel::setName(const std::string &name)
{
	this->name = name;
}

void Channel::setTopic(const std::string &topic)
{
	this->topic = topic;
}

void Channel::setPassword(const std::string &password)
{
	this->password = password;
}

void Channel::setUniqueId(size_t uniqueId)
{
	this->uniqueId = uniqueId;
}

void Channel::setProperties(const ChannelProperties &properties)
{
	this->properties = properties;
}

void Channel::addUserToChannel(User *user)
{
	this->_usersInChannel.push_back(user);
}

std::vector<User *> Channel::getChannelsUsers() const
{
	return this->_usersInChannel;
}

User *Channel::getUserByNickname(const std::string &name)  throw (ChannelGetException)
{
	std::vector<User *>::iterator it = std::find_if(this->_usersInChannel.begin(), this->_usersInChannel.end(), UserPredicateNickname(name));
	if (it != this->_usersInChannel.end())
		return *it;
	std::string chanName = this->name;
	throw ChannelGetException(("No user called " + name + "in channel #" + chanName));
}

bool Channel::isUserInChannel(const std::string &name)
{
	std::vector<User *>::iterator it = std::find_if(this->_usersInChannel.begin(), this->_usersInChannel.end(), UserPredicateNickname(name));
	if (it != this->_usersInChannel.end())
		return true;
	return false;
}

std::string Channel::getUserList()
{
	std::string result;

	for (std::vector<User *>::iterator it = this->_usersInChannel.begin() ; it != this->_usersInChannel.end() ; ++it)
	{
		result += (*it)->getNickname();
		result += " ";
	}
	StringUtils::trim(result, " ");
	return result;
}