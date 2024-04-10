#ifndef CONFIG_HPP
	#define CONFIG_HPP
	#include <string>
	#include <list>
	#include "ConfigurationSection.hpp"

	class Configuration
	{
		public:
			Configuration(const std::string& file);
			~Configuration();
			void load();
			void addSection(ConfigurationSection *section);
			void printSections();
			ConfigurationSection* getSection(const std::string& name);
		private:
			std::string file;
			std::list<ConfigurationSection*> sections;
	};
#endif
