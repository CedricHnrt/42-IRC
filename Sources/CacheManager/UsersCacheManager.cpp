#include "UsersCacheManager.hpp"
#include "UserExceptions.hpp"
#include <limits>
#include <algorithm>
#include <iostream>
#include <IRCPredicate.hpp>
#include <PrimitivePredicate.hpp>

UsersCacheManager* UsersCacheManager::instance = NULL;

UsersCacheManager::UsersCacheManager() : users(std::list<User>()), uniqueIdCounter(0)  {}

void UsersCacheManager::addToCache(User& user) throw (UserCacheException)
{
	if (this->uniqueIdCounter == std::numeric_limits<size_t>::max())
		throw UserCacheException(this->uniqueIdCounter, "Maximum number of users reached !");
	user.setUniqueId(++this->uniqueIdCounter);
	this->users.push_back(user);
}

User& UsersCacheManager::getFromCache(size_t userId) throw (UserCacheException)
{
	std::list<User>::iterator iterator = std::find_if(users.begin(), users.end(), UserPredicate(userId));
	if (iterator != users.end())
		return *iterator;
	throw UserCacheException(userId, "User not found !");
}

void UsersCacheManager::deleteFromCache(size_t userId) throw (UserCacheException)
{
	std::list<User>::iterator iterator = std::find_if(users.begin(), users.end(),  UserPredicate(userId));
	if (iterator != users.end())
	{
		users.erase(iterator);
		return ;
	}
	throw UserCacheException(userId, "User not found !");
}

std::list<User> UsersCacheManager::getCache()
{
	return this->users;
}

size_t UsersCacheManager::getUniqueIdCounter() const
{
	return this->uniqueIdCounter;
}

UsersCacheManager* UsersCacheManager::getInstance()
{
	return instance == NULL ? instance = new UsersCacheManager() : instance;
}