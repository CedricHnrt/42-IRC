#include "IrcLogger.hpp"

#include <Colors.hpp>
#include <ctime>
#include <iostream>

IrcLogger* IrcLogger::instance = NULL;

IrcLogger::IrcLogger() : logFile(NULL), logLevel(TRACE)
{
	this->logFunctions[TRACE] = &IrcLogger::trace;
	this->logFunctions[DEBUG] = &IrcLogger::debug;
	this->logFunctions[INFO] = &IrcLogger::info;
	this->logFunctions[WARN] = &IrcLogger::warn;
	this->logFunctions[ERROR] = &IrcLogger::error;
}
IrcLogger::~IrcLogger()
{
	this->close();
}

void IrcLogger::open(const std::string& file)
{
	this->logFile = new std::ofstream(file.c_str());
}

void IrcLogger::setLogLevel(LogLevel level)
{
	this->logLevel = level;
}

IrcLogger::LogLevel IrcLogger::getLogLevelFromString(const std::string& value)
{
	if (value == "TRACE")
		return TRACE;
	if (value == "DEBUG")
		return DEBUG;
	if (value == "INFO")
		return INFO;
	if (value == "WARN")
		return WARN;
	if (value == "ERROR")
		return ERROR;
	log(IrcLogger::ERROR, "Invalid log level, defaulting to TRACE");
	return TRACE;
}


void IrcLogger::log(LogLevel level, const std::string& message)
{
	std::map<LogLevel, void (IrcLogger::*)(const std::string&)> ::iterator iterator = logFunctions.begin();
	while (iterator != logFunctions.end())
	{
		if (level < logLevel)
		{
			++iterator;
			continue;
		}

		if (iterator->first == level)
		{
			(this->*(iterator->second))(message);
			break;
		}
		++iterator;
	}
}

void IrcLogger::trace(const std::string& message)
{
	Colors gray = Colors(Colors::FG_LGRAY);
	Colors reset = Colors(Colors::RESET);
	std::cout << gray << getCurrentTime() << "[TRACE] " << message  << reset << std::endl;
	*logFile << getCurrentTime() << "[TRACE] " << message << std::endl;
}

void IrcLogger::debug(const std::string& message)
{
	Colors blue = Colors(Colors::FG_BLUE);
	Colors reset = Colors(Colors::RESET);
	std::cout << getCurrentTime() << blue << "[DEBUG] " << message << reset << std::endl;
	*logFile << getCurrentTime() << "[DEBUG] " << message << std::endl;
}

void IrcLogger::info(const std::string& message)
{
	Colors green = Colors(Colors::FG_GREEN);
	Colors reset = Colors(Colors::RESET);
	std::cout << green << getCurrentTime() << "[INFO] " << message << reset << std::endl;
	*logFile << getCurrentTime() << "[INFO] " << message << std::endl;
}

void IrcLogger::warn(const std::string& message)
{
	Colors yellow = Colors(Colors::FG_LYELLOW);
	Colors reset = Colors(Colors::RESET);
	std::cout << yellow << getCurrentTime() << "[WARN] " << message << reset << std::endl;
	*logFile << getCurrentTime() << "[WARN] " << message << std::endl;
}

void IrcLogger::error(const std::string& message)
{
	Colors red = Colors(Colors::FG_LRED);
	Colors reset = Colors(Colors::RESET);
	std::cout << red << getCurrentTime() << "[ERROR] " << message << reset << std::endl;
	*logFile << getCurrentTime() << "[ERROR] " << message << std::endl;
}

void IrcLogger::close()
{
	if (logFile != NULL)
	{
		logFile->close();
		delete logFile;
		logFile = NULL;
	}
}

std::string IrcLogger::getCurrentTime()
{
	std::time_t now = std::time(0);
	std::tm* localTime = std::localtime(&now);

	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "[%H:%M:%S] ", localTime);
	return std::string(buffer);
}

IrcLogger* IrcLogger::getLogger()
{
	return instance == NULL ? instance = new IrcLogger() : instance;
}