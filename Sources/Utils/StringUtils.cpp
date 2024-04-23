#include "StringUtils.hpp"

#include <IrcLogger.hpp>
//#include <regex>
#include <stdexcept>

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

void StringUtils::trim(std::string &str, const char *characters)
{
	const size_t first = str.find_first_not_of(characters);
	const size_t last = str.find_last_not_of(characters);
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

void StringUtils::replaceAll(std::string &line, const std::string &key, const std::string &value)
{
	const std::size_t keyLen = key.length();
	const std::size_t valueLen = value.length();

	try {
			const std::size_t stringLen = line.length();
			for (std::size_t charIndex = 0; charIndex < stringLen; charIndex++) {
				size_t pos = line.find(key, charIndex);
				if (pos == std::string::npos)
					continue;
				line.erase(pos, keyLen);
				line.insert(pos, value);
				charIndex = pos + valueLen;
			}
	}
	catch (const std::exception &e) {
		std::string trace = "Exception throws during replace :";
		trace.append(e.what());
		throw std::out_of_range(trace);
	}
}

std::vector<std::string> StringUtils::split(const std::string &input, int c)
{
	std::vector<std::string> result;
	if (input.empty())
		return result;

	if (input.find(c) == std::string::npos) {
		result.push_back(input);
		IrcLogger::getLogger()->log(IrcLogger::WARN, "No delimiter found in the input string");
		return result;
	}

	size_t i = input.find(c);
	size_t j = 0;
	std::string line;

	while (input[i])
	{
		i = input.find(c, j);
		if (i == std::string::npos) {
			result.push_back(input.substr(j, i - j));
			break;
		}
		line = input.substr(j, i - j);
		i++;
		j = i;
		result.push_back(line);
		line.clear();
	}
	for (std::vector<std::string>::iterator it = result.begin(); it != result.end(); ++it)
	{
		StringUtils::trim(*it,"\r\n ");
	}
	return result;
}

std::string StringUtils::ltos(long value)
{
	std::string result;
	while (value)
	{
		result = static_cast<char>((value % 10) + '0') + result;
		value /= 10;
	}
	return result;
}


void StringUtils::keepOnlyUsefulChar(std::string &input, const std::string toKeep)
{
	for (std::string::iterator it = input.begin(); it != input.end(); ++it) {
		if (toKeep.find(*it) == std::string::npos)
			input.erase(it);
	}
}

static std::string generateCensuredWord(std::string word, char c)
{
	std::string censuredWord = "";
	std::string::iterator begin = word.begin();
	while (begin != word.end())
	{
		censuredWord += c;
		censuredWord += c;
		++begin;
	}
	return censuredWord;
}

std::vector<std::string> StringUtils::generateCensuredStrings(std::vector<std::string> words)
{
	std::vector<std::string> censuredWords;
	int index = 32;
	int limit = 126;
	std::vector<std::string>::iterator it = words.begin();
	while (it != words.end())
	{
		std::string UPPER_WORD = *it;
		StringUtils::toUpper(UPPER_WORD);
		while (index < limit)
		{
			char c = index;
			censuredWords.push_back(generateCensuredWord(UPPER_WORD, c));
			++index;
		}
		++it;
	}
	return censuredWords;
}

std::pair<bool, std::string> StringUtils::hasCensuredWord(std::string word, std::vector<std::string> censuredWords)
{
	std::vector<std::string>::iterator it = censuredWords.begin();
	while (it != censuredWords.end())
	{
		if (word.find(*it) != std::string::npos)
			return std::make_pair(true, *it);
		++it;
	}
	return std::make_pair(false, "");
}
