#include "StringUtils.hpp"

bool StringUtils::isAscii(const std::string str)
{
	for (std::string::size_type i = 0; i < str.size(); ++i)
	{
		const int character = static_cast<unsigned char>(str[i]);
		if (character < 0 || character > 127)
			return false;
	}
	return true;
}

bool StringUtils::isOnlyWhitespace(const std::string str)
{
	for (std::string::size_type i = 0; i < str.size(); ++i)
	{
		const char character = (str[i]);
		if (!std::isspace(character))
			return false;
	}
	return true;
}

bool StringUtils::isOnlyDigits(const std::string str)
{
	for (std::string::size_type i = 0; i < str.size(); ++i)
	{
		const char character = (str[i]);
		if (!std::isdigit(character))
			return false;
	}
	return true;
}

bool StringUtils::isAlpha(const std::string str)
{
	for (std::string::size_type i = 0; i < str.size(); ++i)
	{
		const char character = (str[i]);
		if (!std::isalpha(character))
			return false;
	}
	return true;
}

bool StringUtils::isAlphaNumeric(const std::string str)
{
	for (std::string::size_type i = 0; i < str.size(); ++i)
	{
		const char character = (str[i]);
		if (!std::isalnum(character))
			return false;
	}
	return true;
}

bool StringUtils::isPrintable(const std::string str)
{
	for (std::string::size_type i = 0; i < str.size(); ++i)
	{
		const char character = (str[i]);
		if (!std::isprint(character))
			return false;
	}
	return true;
}

void StringUtils::trim(std::string &str, const char character)
{
	const size_t first = str.find_first_not_of(character);
	const size_t last = str.find_last_not_of(character);
	str = str.substr(first, (last - first + 1));
}

void StringUtils::toUpper(std::string &str)
{
	for (std::string::size_type i = 0; i < str.size(); ++i)
	{
		char &character = (str[i]);
		character = static_cast<char> (std::toupper(character));
	}
}

void StringUtils::toLower(std::string &str)
{
	for (std::string::size_type i = 0; i < str.size(); ++i)
	{
		char &character = (str[i]);
		character = static_cast<char> (std::tolower(character));
	}
}