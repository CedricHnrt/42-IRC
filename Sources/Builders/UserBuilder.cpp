#include "UserBuilder.hpp"

UserBuilder::UserBuilder() : userSocketFd(-1) {}

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

UserBuilder	&UserBuilder::fillBuffer(const std::string data, int incomingFD)
{
	this->userSocketFd = incomingFD;
	this->uniqueId = incomingFD;
	std::vector<std::string> incomingData = StringUtils::split(data, '\n');

	for (std::vector<std::string>::iterator it  = incomingData.begin(); it != incomingData.end(); ++it) {
		this->connectionInfos.push_back(*it);
	}
	return *this;
}

bool UserBuilder::isBuilderComplete() throw (UserBuildException)
{
	if (this->connectionInfos.size() >= 3 && this->connectionInfos.back().substr(0, 4) == "USER")
	{
		this->connectionInfos.erase(this->connectionInfos.begin());

		std::string newUserName = "New connection";

		/*handle the password*/
		std::vector<std::string> passwordV = StringUtils::split(this->connectionInfos.front(), ' ');
		if (passwordV.size() != 2 || passwordV[1] != Configuration::getInstance()->getSection("SERVER")->getStringValue("password")) {
			sendServerReply(this->userSocketFd, ERR_PASSWDMISMATCH(newUserName), RED, BOLDR);
			throw UserBuildException("Invalid Password");
		}

		this->connectionInfos.erase(this->connectionInfos.begin());

		/*handle the nickname*/
		std::vector<std::string> nickname = StringUtils::split(this->connectionInfos.front(), ' ');
		this->nickname = nickname[1];

		if (UsersCacheManager::getInstance()->doesNicknameAlreadyExist(this->nickname)) {
			sendServerReply(this->userSocketFd, ERR_ALREADYREGISTERED(this->nickname), RED, BOLDR);
			throw UserBuildException("Nickname already exists");
		}


		this->connectionInfos.erase(this->connectionInfos.begin());

		/*handle username*/
		std::vector<std::string> username =  StringUtils::split(this->connectionInfos.front(), ' ');
		if (username.size() != 5) {
			return false;
		}
		this->userName = username[1];
		StringUtils::trim(username[4], " :\n");
		this->realName = username[4];

		IrcLogger *logger = IrcLogger::getLogger();
		logger->log(IrcLogger::DEBUG, "UserBuilder is complete !");
		logger->log(IrcLogger::DEBUG, "Username: " + this->userName);
		logger->log(IrcLogger::DEBUG, "Nickname: " + this->nickname);
		logger->log(IrcLogger::DEBUG, "RealName: " + this->realName);
		logger->log(IrcLogger::DEBUG, "Password: " + passwordV[1]);
		return true;
	}
	return false;
}