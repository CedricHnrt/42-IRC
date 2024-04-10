#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include <string>

class StringUtils
{
public:
	static bool isAscii(const std::string str);
	static bool isPrintable(const std::string str);
	static bool isOnlyWhitespace(const std::string str);
	static bool isOnlyDigits(const std::string str);
	static bool isAlpha(const std::string str);
	static bool isAlphaNumeric(const std::string str);
	static void trim(std::string &str, const char character);
	static void toUpper(std::string &str);
	static void toLower(std::string &str);
};

#endif //STRINGUTILS_H