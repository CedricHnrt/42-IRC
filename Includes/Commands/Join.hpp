//
// Created by pgouasmi on 4/16/24.
//

#ifndef INC_42_IRC_JOIN_HPP
#define INC_42_IRC_JOIN_HPP

#include "ICommand.hpp"
#include <vector>


class Join : public ICommand {

public:
	Join();
	void execute(User *user, Channel *channel, std::vector<std::string>args);
};


#endif //INC_42_IRC_JOIN_HPP
