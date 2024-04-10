#include "ChannelExceptions.hpp"

ChannelNotFoundException::ChannelNotFoundException(size_t channelId, const std::string& message) throw() :
message(message), channelId(channelId) {}

ChannelNotFoundException::~ChannelNotFoundException() throw() {}

const char* ChannelNotFoundException::what() const throw()
{
    return message.c_str();
}