#include "../../Includes/Channel/Exceptions/ChannelException.hpp"

ChannelCreationException::ChannelCreationException(const std::string& message) throw() :
message(message) {}

ChannelCreationException::~ChannelCreationException() throw() {}

const char* ChannelCreationException::what() const throw()
{
    return message.c_str();
}