#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP
	#include <string>
	#include "../User/User.hpp"
	#include "../Channel/Channel.hpp"
	#include "ArgumentsTypes.hpp"

	class ICommand {
		public:
			virtual std::string getName() const = 0;
			virtual std::string getDescription() const = 0;
			virtual std::string getUsage() const = 0;
			virtual void getArgs(ArgumentsType* args) const = 0;
			virtual std::string getPermission() const = 0;
			virtual void execute(User user, Channel channel) const = 0;
	};
#endif
