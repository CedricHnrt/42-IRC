#ifndef CHANNELEXCEPTION_HPP
#define CHANNELEXCEPTION_HPP
#include <exception>
#include <string>

class ChannelNotFoundException : public std::exception
{
	private:
		std::string message;
		size_t channelId;
	public:
		ChannelNotFoundException(size_t channelId, const std::string& message) throw() ;
		~ChannelNotFoundException() throw();
		const char *what() const throw();
};

class ChannelCreationException : public std::exception
{
	private:
		std::string message;
	public:
		ChannelCreationException(const std::string& message) throw();
		~ChannelCreationException() throw();
		const char *what() const throw();
};

class ChannelDeletionException : public std::exception
{
	private:
		std::string message;
		size_t channelId;
	public:
		ChannelDeletionException(size_t channelId, const std::string& message) throw();
		~ChannelDeletionException() throw();
		const char *what() const throw();
};

class ChannelModificationException : public std::exception
{
	private:
		std::string message;
		size_t channelId;
	public:
		ChannelModificationException(size_t channelId, const std::string& message) throw();
		~ChannelModificationException() throw();
		const char *what() const throw();
};
#endif
