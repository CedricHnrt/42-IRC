#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include <string>
#include <vector>

class StringUtils
{
public:
	static bool isAscii(const std::string str);
	static bool isPrintable(const std::string str);
	static bool isOnlyWhitespace(const std::string str);
	static bool isOnlyDigits(const std::string str);
	static bool isAlpha(const std::string str);
	static bool isAlphaNumeric(const std::string str);
	static void trim(std::string &str, const char *characters);
	static void toUpper(std::string &str);
	static void toLower(std::string &str);
	static std::vector<std::string>split(const std::string &input, int c);
};

#endif //STRINGUTILS_H