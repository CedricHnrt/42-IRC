#ifndef USER_HPP
	#define USER_HPP

	#include <string>
	class UserProperties;

	class User {
		private:
			std::string name;
			std::string realName;
			std::string nickname;
			std::string ipAddr;
			int userSocketFd;
			size_t uniqueId;
			UserProperties* properties;
		public:
			std::string getName() const;
			std::string getRealName() const;
			std::string getNickname() const;
			std::string getIpAddr() const;
			int getUserSocketId() const;
			size_t getUniqueId() const;
			UserProperties getProperties() const;

			User& setName(const std::string& name);
			User& setNickname(const std::string& nickname);
			User& setRealName(const std::string& realName);
			User& setIpAddr(const std::string& ipAddr);
			User& setUserSocketId(int userSocketFd);
			User& setUniqueId(const size_t& uniqueId);
			User& setProperties(const UserProperties& properties);
	};

#endif
