#include "ConfigurationExceptions.hpp"

ConfigurationIOException::ConfigurationIOException(const std::string& message) throw() : message(message) {}

ConfigurationIOException::~ConfigurationIOException() throw() {}

const char *ConfigurationIOException::what() const throw()
{
	return message.c_str();
}
