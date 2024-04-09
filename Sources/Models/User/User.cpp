#include "User.hpp"
#include "UserProperties.hpp"

std::string User::getName() const
{
	return name;
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

User User::setName(const std::string& name)
{
	this->name = name;
	return *this;
}

User User::setNickname(const std::string& nickname)
{
	this->nickname = nickname;
	return *this;
}

User User::setIpAddr(const std::string& ipAddr)
{
	this->ipAddr = ipAddr;
	return *this;
}

User User::setUniqueId(const size_t& uniqueId)
{
	this->uniqueId = uniqueId;
	return *this;
}

User User::setProperties(const UserProperties& properties)
{
	*this->properties = properties;
	return *this;
}

