#include "User.hpp"
#include "UserProperties.hpp"

User::User() {}

std::string User::getUserName() const
{
	return userName;
}

std::string User::getNickname() const
{
	return nickname;
}

std::string User::getIpAddr() const
{
	return ipAddr;
}

size_t User::getUniqueId() const
{
	return uniqueId;
}

UserProperties User::getProperties() const
{
	return *properties;
}

void User::setName(const std::string& name)
{
	this->userName = name;
}

void User::setNickname(const std::string& nickname)
{
	this->nickname = nickname;
}

void User::setIpAddr(const std::string& ipAddr)
{
	this->ipAddr = ipAddr;
}

void User::setUniqueId(const size_t& uniqueId)
{
	this->uniqueId = uniqueId;
}

void User::setProperties(const UserProperties& properties)
{
	*this->properties = properties;
}

void User::setUserSocketId(int userSocketFd)
{
	this->userSocketFd = userSocketFd;
}

int User::getUserSocketId() const
{
	return userSocketFd;
}

void User::setRealName(const std::string& realName)
{
	this->realName = realName;
}

std::string User::getRealName() const
{
	return realName;
}

