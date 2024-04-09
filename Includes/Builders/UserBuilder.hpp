#ifndef USERBUILDER_HPP
	#define USERBUILDER_HPP

	#include <string>
	#include "User.hpp"
	#include "UserProperties.hpp"
	class UserBuilder {
		private:
			std::string name;
			std::string realName;
			std::string nickname;
			std::string ipAddr;
			int userSocketFd;
			size_t uniqueId;
			UserProperties properties;

		public:
			UserBuilder();
			UserBuilder& setName(const std::string& name);
			UserBuilder& setRealName(const std::string& realName);
			UserBuilder& setNickname(const std::string& nickname);
			UserBuilder& setIpAddr(const std::string& ipAddr);
			UserBuilder& setUserSocketId(int userSocketFd);
			UserBuilder& setProperties(const UserProperties& properties);
			void clearBuilder();
			User& build();
	};
#endif
