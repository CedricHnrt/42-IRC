#include "ChannelBuilder.hpp"

#include <StringUtils.hpp>
#include <ChannelExceptions.hpp>
#include "Channel.hpp"

ChannelBuilder& ChannelBuilder::setName(const std::string& name) {
	this->name = name;
	return *this;
}

ChannelBuilder& ChannelBuilder::setTopic(const std::string& topic) {
	this->topic = topic;
	return *this;
}

ChannelBuilder& ChannelBuilder::setPassword(const std::string& password) {
	this->password = password;
	return *this;
}

ChannelBuilder& ChannelBuilder::setProperties(const ChannelProperties& properties)
{
	this->properties = properties;
	return *this;
}

#include <iostream>
static bool isValid(bool authorizeEmpty, std::string str) {
	if ((!authorizeEmpty && str.empty()) || str.length() > 255) {
		std::cout << "first if KO" << std::endl;
		return false;
	}
	if ((!authorizeEmpty && StringUtils::isOnlyWhitespace(str)) || (!authorizeEmpty && !StringUtils::isPrintable(str))) {
		std::cout << "second if KO" << std::endl;
		return false;
	}
	return true;
}

void ChannelBuilder::clearBuilder() {
	this->name.clear();
	this->topic.clear();
	this->password.clear();
	this->properties.getInvited().clear();
	this->properties.getOperators().clear();
	this->properties.getBannedUsers().clear();
	this->properties.getMutedUsers().clear();
	this->properties.getUsersInChannel().clear();
}

Channel *ChannelBuilder::build() {

	//TODO: FIX NULL POINTER EXCEPTION WHEN PROPERTIES IS NOT SET
	//TODO: ADD GOOD EXCEPTIONS
	if (!isValid(false, this->name))
		clearBuilder();
	if (!isValid(true, this->topic) || !isValid(true, this->password))
		clearBuilder();

	Channel* channel = new Channel();
	channel->setName(this->name);
	channel->setTopic(this->topic);
	channel->setPassword(this->password);
	//TODO: FIX NULL POINTER EXCEPTION WHEN PROPERTIES IS NOT SET
	//user->setProperties(this->properties);

	clearBuilder();

	return (channel);
}