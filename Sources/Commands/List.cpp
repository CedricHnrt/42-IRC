#include "List.hpp"

List::List()
{
	this->_name = "LIST";
	this->_description = "List all channels";
	this->_usage = "/list";
	this->_permissionLevel = 0;
}

void List::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void)args;
	(void)channel;
	std::string channelName = "TEST";
	std::string channelTopic = "TEST TOPIC";
	sendServerReply(user->getUserSocketFd(), RPL_LIST(user->getUserName(), channelName, 5, channelTopic), GREY, ITALIC);
}