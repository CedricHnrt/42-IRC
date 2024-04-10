#include "Configuration.hpp"
#include "FileUtils.hpp"
#include "StringUtils.hpp"
#include <iostream>

Configuration::Configuration(const std::string &file) : file(file) {}

Configuration::~Configuration()
{
	std::list<ConfigurationSection *>::iterator sectionIterator = sections.begin();
	while (sectionIterator != sections.end())
	{
		delete *sectionIterator;
		sectionIterator++;
	}
	sections.clear();
}

void Configuration::load()
{
	if (file.empty() || StringUtils::isOnlyWhitespace(file) || !StringUtils::isPrintable(file))
		throw std::invalid_argument("Filename is invalid !");
	if (FileUtils::isDirectory(file))
		throw std::invalid_argument("File can't be a folder");

	std::ifstream configurationFileStream(file.c_str());

	if (!configurationFileStream.is_open())
	{
		std::cout << "Error: " << file << " could not be opened" << std::endl;
		return;
	}

	size_t linesCount = FileUtils::countLines(configurationFileStream);
	std::list<std::string> lines;
	FileUtils::readFromFile(configurationFileStream, lines, linesCount);
	configurationFileStream.close();

	std::list<std::string>::iterator linesIterator = lines.begin();
	while (linesIterator != lines.end())
	{
		std::string line = *linesIterator;
		if (line.empty() || StringUtils::isOnlyWhitespace(line) || !StringUtils::isPrintable(line))
		{
			++linesIterator;
			continue;
		}

		if (line[0] == '[' && line[line.size() - 1] == ']')
		{
			ConfigurationSection *section = new ConfigurationSection(line.substr(1, line.size() - 2));
			sections.push_back(section);
			++linesIterator;
			while (linesIterator != lines.end())
			{
				line = *linesIterator;
				if (line.empty() || StringUtils::isOnlyWhitespace(line) || !StringUtils::isPrintable(line))
				{
					++linesIterator;
					continue;
				}
				if (line[0] == '[' && line[line.size() - 1] == ']')
					break;
				size_t equalPos = line.find("=");
				if (equalPos != std::string::npos)
				{
					std::string key = line.substr(0, equalPos -1);
					std::string value = line.substr(equalPos + 2);
					if (value[0] && value[value.size() - 1] == '"')
						value = value.substr(1, value.size() - 2);
					section->addEntry(key, value);
				}
				++linesIterator;
			}
		}
	}
}

void Configuration::addSection(ConfigurationSection *section)
{
	sections.push_back(section);
}

void Configuration::printSections()
{
	std::cout << "CONFIGURATION FILE: " << file << std::endl;
	std::cout << "                    " << sections.size() << " SECTIONS WAS FOUNDED" << std::endl;
	std::list<ConfigurationSection *>::iterator sectionIterator = sections.begin();
	while (sectionIterator != sections.end())
	{
		std::cout << "                    SECTION: " << (*sectionIterator)->getName() << std::endl;
		std::cout << "                     ENTRIES: " << (*sectionIterator)->getValues().size() << " WAS LOADED" << std::endl;
		std::map<std::string, std::string>::iterator entryIterator = (*sectionIterator)->getValues().begin();
		while (entryIterator != (*sectionIterator)->getValues().end())
		{
			std::cout << "                      " << entryIterator->first << "=" << entryIterator->second << std::endl;
			entryIterator++;
		}
		sectionIterator++;
	}
}

ConfigurationSection *Configuration::getSection(const std::string &name)
{
	std::list<ConfigurationSection *>::iterator sectionIterator = sections.begin();
	while (sectionIterator != sections.end())
	{
		if ((*sectionIterator)->getName() == name)
			return *sectionIterator;
		sectionIterator++;
	}
	std::cerr << "Error: Section " << name << " not found" << std::endl;
	return NULL;
}
