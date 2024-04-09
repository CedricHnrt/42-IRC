#include "../../Includes/Channel/Exceptions/ChannelException.hpp"

ChannelDeletionException::ChannelDeletionException(size_t channelId, const std::string& message) throw() :
message(message), channelId(channelId) {}

ChannelDeletionException::~ChannelDeletionException() throw() {}

const char* ChannelDeletionException::what() const throw()
{
	return message.c_str();
}