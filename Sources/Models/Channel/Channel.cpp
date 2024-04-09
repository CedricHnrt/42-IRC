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