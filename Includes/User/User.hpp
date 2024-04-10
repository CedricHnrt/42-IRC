#ifndef USER_HPP
	#define USER_HPP

	#include <string>
	class UserProperties;

	class User {
		private:
			User();
			std::string userName;
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
			void setNickname(const std::string& nickname);

		private:
			friend class UserBuilder;
			friend class UsersCacheManager;
			void setName(const std::string& name);
			void setRealName(const std::string& realName);
			void setIpAddr(const std::string& ipAddr);
			void setUserSocketId(int userSocketFd);
			void setUniqueId(const size_t& uniqueId);
			void setProperties(const UserProperties& properties);
	};

#endif
