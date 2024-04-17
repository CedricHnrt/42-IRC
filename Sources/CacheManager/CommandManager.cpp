//
// Created by pgouasmi on 4/16/24.
//

#include "CommandManager.hpp"
#include "Join.hpp"

CommandManager* CommandManager::instance = NULL;

CommandManager::CommandManager()
{
	//NEED TO ADD
	//creer kick
	this->_commandsMap["JOIN"] = new Join();
}

CommandManager::~CommandManager()
{
	for (std::map<std::string, ICommand *>::iterator it = this->_commandsMap.begin(); it != this->_commandsMap.end(); ++it) {
		delete it->second;
	}
}

CommandManager *CommandManager::getInstance()
{
	return instance == NULL ? instance = new CommandManager() : instance;
}

ICommand *CommandManager::getCommand(const std::string &key) const
{
	if (this->doesCommandExist(key))
		return this->_commandsMap.at(key);
	return NULL;
}

bool CommandManager::doesCommandExist(const std::string &key) const
{
	return this->_commandsMap.find(key) != _commandsMap.end() ? true : false;
}
