//
// Created by pgouasmi on 4/23/24.
//

#ifndef MODE_HPP
#define MODE_HPP

#include "ICommand.hpp"


class Mode : public ICommand {
public:
	Mode();
	void execute(User *user, Channel *channel, std::vector<std::string>args);
};


#endif
