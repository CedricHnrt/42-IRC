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

static bool isValid(bool authorizeEmpty, std::string str) {
	if ((authorizeEmpty && str.empty()) || str.length() > 255)
		return false;
	if (StringUtils::isOnlyWhitespace(str) || !StringUtils::isPrintable(str))
		return false;
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

Channel& ChannelBuilder::build() {

	//TODO: FIX NULL POINTER EXCEPTION WHEN PROPERTIES IS NOT SET
	//TODO: ADD GOOD EXCEPTIONS
	if (!isValid(false, this->name))
		clearBuilder();
	if (!isValid(true, this->topic) || !isValid(true, this->password))
		clearBuilder();

	Channel* channel = new Channel();
	if (this->name.c_str())
		channel->setName(this->name);
	if (this->topic.c_str())
		channel->setTopic(this->topic);
	if (this->password.c_str())
		channel->setPassword(this->password);
	//TODO: FIX NULL POINTER EXCEPTION WHEN PROPERTIES IS NOT SET
	//user->setProperties(this->properties);
	clearBuilder();

	return (*channel);
}