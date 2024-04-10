#include "ChannelExceptions.hpp"

ChannelModificationException::ChannelModificationException(size_t channelId, const std::string& message) throw() :
message(message), channelId(channelId) {}

ChannelModificationException::~ChannelModificationException() throw() {}

const char* ChannelModificationException::what() const throw()
{
	return message.c_str();
}