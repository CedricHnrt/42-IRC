#include "ConfigurationSection.hpp"
#include <cstdlib>
#include <cerrno>

ConfigurationSection::ConfigurationSection(const std::string &name) : name(name) {}

const std::string &ConfigurationSection::getName() const
{
	return this->name;
}

void ConfigurationSection::addEntry(const std::string &key, const std::string &value)
{
	this->map[key] = value;
}

std::string ConfigurationSection::getStringValue(const std::string &key, std::string defaultValue)
{
	if (this->map.find(key) == this->map.end())
		return defaultValue;
	return this->map[key];
}

size_t ConfigurationSection::getNumericValue(const std::string &key, size_t defaultValue)
{
	if (this->map.find(key) == this->map.end())
		return defaultValue;
	const size_t value = std::strtol(this->map[key].c_str(), NULL, 10);
	if (errno == ERANGE || errno != 0)
		return defaultValue;
	return value;
}

bool ConfigurationSection::getBooleanValue(const std::string &key, bool defaultValue)
{
	if (this->map.find(key) == this->map.end())
		return defaultValue;
	return this->map[key] == "true";
}

std::map<std::string, std::string> &ConfigurationSection::getValues()
{
	return this->map;
}