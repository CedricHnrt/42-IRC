#ifndef USERCACHEMANAGER_HPP
#define USERCACHEMANAGER_HPP

	#include "User.hpp"
	#include <list>

	class UsersCacheManager
	{
		private:
			static UsersCacheManager* instance;
			std::list<User> users;
			size_t uniqueIdCounter;
			UsersCacheManager();

		public:
			void addToCache(User& user);
			User& getFromCache(size_t uniqueId);
			User& getFromCacheSocketFD(int socketFD);
			void deleteFromCache(size_t uniqueId);
			std::list<User> getCache();
			size_t getUniqueIdCounter() const;
			static UsersCacheManager* getInstance();
	};


#endif
