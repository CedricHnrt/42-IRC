#ifndef CHANNELBUILDER_HPP
#define CHANNELBUILDER_HPP

#include <string>
#include "../Channel/Channel.hpp"
#include "../Channel/ChannelProperties.hpp"

class ChannelBuilder {
private:
	std::string name;
	std::string topic;
	std::string password;
	ChannelProperties properties;

public:
	ChannelBuilder& setName(const std::string& name);
	ChannelBuilder& setTopic(const std::string& topic);
	ChannelBuilder& setPassword(const std::string& password);
	ChannelBuilder& setProperties(const ChannelProperties& properties);
	void clearBuilder();
	Channel& build();
};

#endif