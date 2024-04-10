#include "UserBuilder.hpp"

#include <StringUtils.hpp>
#include <UserExceptions.hpp>
#include "User.hpp"

#include <iostream>

#define PASSWORD "test"

UserBuilder::UserBuilder() : userSocketFd(-1), isComplete(false) {}

UserBuilder& UserBuilder::setName(const std::string& name) {
	this->userName = name;
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
	this->userName.clear();
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

	if (!isValid(this->userName))
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
	if (this->userName.c_str())
		user->setName(this->userName);
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

UserBuilder	&UserBuilder::fillBuffer(const std::string data)
{
//	std::cout << "got in fillBuffer, data = " << data << std::endl;

	std::string line;
	size_t i = 0;
	size_t j = 0;

	while (data[i] && data[i + 1])
	{
		i = data.find('\n', j);
		line = data.substr(j, i - j);
		i++;
		j = i;
//		std::cout << "line: " << line << std::endl;
		this->connectionInfos.push_back(line);
	}
//	std::cout << "end of fill buffer, size=" << this->connectionInfos.size() << std::endl;
	return *this;
}

bool UserBuilder::isBuilderComplete()
{
	std::string line;

	std::cout << "in BUILDER COMPLETE\n" << std::endl;
//
//	std::cout << "in builder complete, last info in vector: " << this->connectionInfos.back().substr(0, 4) << std::endl;

	if (this->connectionInfos.size() >= 3 && this->connectionInfos.back().substr(0, 4) == "USER")
	{
		this->connectionInfos.erase(this->connectionInfos.begin());

		/*handle the password*/
		if (this->connectionInfos[0].substr(0, 4) != "PASS")
			return false;
		std::string password = this->connectionInfos[0].substr(5, this->connectionInfos[0].length());
		password.erase(password.find(13));
		std::cout << "password: " << password << ", size: " << password.size() << std::endl;
		if (password != PASSWORD)
			return false;

		this->connectionInfos.erase(this->connectionInfos.begin());

		/*handle the nickname*/
		std::string nickname = this->connectionInfos[0].substr(5, this->connectionInfos[0].length());
		nickname.erase(nickname.find(13));
		this->nickname = nickname;

		std::cout << "nickname =" << nickname << std::endl;

		this->connectionInfos.erase(this->connectionInfos.begin());

		/*handle username*/
		std::cout << "username line= " << this->connectionInfos[0] << std::endl;
		std::vector<std::string> temp;

		size_t i = 0;
		size_t j = 0;

		while (this->connectionInfos[0][i] && this->connectionInfos[0][i + 1])
	{
		i = this->connectionInfos[0].find('\n', j);
		line = this->connectionInfos[0].substr(j, i - j);
		i++;
		j = i;
//		std::cout << "line: " << line << std::endl;
		this->connectionInfos.push_back(line);
	}

		std::cout << "username: " << this->userName << std::endl;

		return true;
	}
	return false;
}