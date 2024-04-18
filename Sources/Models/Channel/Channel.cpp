#include "Channel.hpp"
#include "ChannelProperties.hpp"

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

ChannelProperties Channel::getProperties() const
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

User *Channel::getUserByName(const std::string &name)
{
	for (std::vector<User*>::iterator it = this->_usersInChannel.begin() ; it != this->_usersInChannel.end() ; ++it)
	{
		if ((*it)->getUserName() == name)
			return *it;
	}
	return NULL;
}