#ifndef IRC_PART_HPP
# define IRC_PART_HPP

# include "ICommand.hpp"

class Part : public ICommand
{
	public :
		Part();
		void execute(User *user, Channel *channel, std::vector<std::string>args);
};

#endif //IRC_PART_HPP
