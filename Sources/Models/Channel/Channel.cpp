#include "Channel.hpp"
#include "ChannelProperties.hpp"
#include "ChannelManager.hpp"

Channel::Channel(std::string name, std::string topic, std::string password) : name(name), topic(topic), password(password)
{
	this->uniqueId = 1;
}

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

Channel Channel::setName(const std::string &name)
{
	this->name = name;
	return *this;
}

Channel Channel::setTopic(const std::string &topic)
{
	this->topic = topic;
	return *this;
}

Channel Channel::setPassword(const std::string &password)
{
	this->password = password;
	return *this;
}

Channel Channel::setUniqueId(size_t uniqueId)
{
	this->uniqueId = uniqueId;
	return *this;
}

Channel Channel::setProperties(const ChannelProperties &properties)
{
	ChannelManager::getInstance()->getChannels();
	this->properties = properties;
	return *this;
}
