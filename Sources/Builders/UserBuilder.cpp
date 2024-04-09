#include "UserBuilder.hpp"

#include <StringUtils.hpp>
#include <UserExceptions.hpp>
#include "User.hpp"

UserBuilder::UserBuilder() : userSocketFd(-1) {}

UserBuilder& UserBuilder::setName(const std::string& name) {
	this->name = name;
	return *this;
}

UserBuilder& UserBuilder::setRealName(const std::string& realName) {
	this->realName = realName;
	return *this;
}

UserBuilder& UserBuilder::setNickname(const std::string& nickname) {
	this->nickname = nickname;
	return *this;
}

UserBuilder& UserBuilder::setIpAddr(const std::string& ipAddr) {
	this->ipAddr = ipAddr;
	return *this;
}

UserBuilder& UserBuilder::setUserSocketId(int userSocketFd) {
	this->userSocketFd = userSocketFd;
	return *this;
}

UserBuilder& UserBuilder::setProperties(const UserProperties& properties) {
	this->properties = properties;
	return *this;
}

static bool isValid(std::string str) {
	if (str.empty() || str.length() > 255)
		return false;
	if (StringUtils::isOnlyWhitespace(str) || !StringUtils::isPrintable(str))
		return false;
	return true;
}

void UserBuilder::clearBuilder() {
	this->name.clear();
	this->realName.clear();
	this->nickname.clear();
	this->ipAddr.clear();
	this->userSocketFd = -1;
	this->properties.setAway(false);
	this->properties.getPermissions().clear();
	this->properties.getBlockedUsers().clear();
	this->properties.getIgnoredUsers().clear();
	this->properties.getJoinedChannels().clear();
	this->properties.getNotifiedConnectionUsers().clear();
}

User& UserBuilder::build() {

	if (!isValid(this->name))
	{
		clearBuilder();
		throw UserBuildException("Invalid Name");
	}
	if (!isValid(this->realName))
	{
		clearBuilder();
		throw UserBuildException("Invalid Real Name");
	}
	if (!isValid(this->nickname))
	{
		clearBuilder();
		throw UserBuildException("Invalid Nickname");
	}
	if (this->userSocketFd == -1)
	{
		clearBuilder();
		throw UserBuildException("Invalid User Socket Id");
	}

	User* user = new User();
	if (this->name.c_str())
		user->setName(this->name);
	if (this->realName.c_str())
		user->setRealName(this->realName);
	if (this->nickname.c_str())
		user->setNickname(this->nickname);
	if (this->ipAddr.c_str())
		user->setIpAddr(this->ipAddr);
	if (this->userSocketFd != -1)
		user->setUserSocketId(this->userSocketFd);
	//TODO: FIX NULL POINTER EXCEPTION WHEN PROPERTIES IS NOT SET
	//user->setProperties(this->properties);
	clearBuilder();

	return (*user);
}