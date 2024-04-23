#ifndef USERCACHEMANAGER_HPP
#define USERCACHEMANAGER_HPP

	#include "User.hpp"
	#include "UserExceptions.hpp"
	#include <list>

	class UsersCacheManager
	{
		private:
			static UsersCacheManager* instance;
			std::list<User *> users;
			std::list<User *> leftUsers;
			size_t uniqueIdCounter;
			UsersCacheManager();

		public:
			void addToCache(User *user) throw(UserCacheException);
			void addToLeftCache(User* user) throw(UserCacheException);
			User* getFromCache(size_t uniqueId) throw(UserCacheException);
			User* getFromCacheSocketFD(int socketFD) throw(UserCacheException);
			User* getFromNickname(std::string &nickname) throw (UserCacheExceptionString);
			bool doesNicknameAlreadyExist(const std::string &nickname) const;
			void deleteFromCache(size_t uniqueId) throw(UserCacheException);
			void UsersCacheManager::deleteTimeoutUsers(std::string serverName);
			std::list<User *> getCache();
			size_t getUniqueIdCounter() const;
			static UsersCacheManager* getInstance();
			~UsersCacheManager();
	};
#endif
