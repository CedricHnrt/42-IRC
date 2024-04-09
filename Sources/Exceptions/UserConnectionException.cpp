#include <string>
#include <Exceptions/UserExceptions.hpp>
UserConnectionException::UserConnectionException(const std::string& message) throw() : message(message) {}

UserConnectionException::~UserConnectionException() throw() {}

const char* UserConnectionException::what() const throw()
{
	return message.c_str();
}