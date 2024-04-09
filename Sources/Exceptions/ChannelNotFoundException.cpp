#include "../../Includes/Channel/Exceptions/ChannelException.hpp"

ChannelNotFoundException::ChannelNotFoundException(size_t channelId, const std::string& message) throw() :
message(message), channelId(channelId) {}

ChannelNotFoundException::~ChannelNotFoundException() throw() {}

const char* ChannelNotFoundException::what() const throw()
{
    std::string msg = channelId + ": " + this->message;
    return msg.c_str();
}