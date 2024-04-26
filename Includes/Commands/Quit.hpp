#ifndef IRC_QUIT_HPP
# define IRC_QUIT_HPP

#include "ICommand.hpp"

class Quit : public ICommand {
	public:
		Quit();
		void execute(User *user, Channel *channel, std::vector<std::string>args);
		void sendQuitMessageToChan(Channel *channel, User *leftUser, const std::string& message);
};

#endif //IRC_QUIT_HPP
