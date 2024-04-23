/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:48:17 by jbadaire          #+#    #+#             */
/*   Updated: 2024/04/23 14:48:17 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"

#include <Server.hpp>

Nick::Nick()
{
	this->_name = "NICK";
	this->_description = "Change your nickname";
	this->_usage = "/Nick <new nickname>";
	this->_permissionLevel = 0;
	this->_expectedArgs.push_back(STRING);
}

void Nick::execute(User *user, Channel *channel, std::vector<std::string> args)
{
	(void)user;
	(void)args;

	std::string newNick = args[0];
	bool newNickIsOk = true;

	//TODO: Check if the nickname is already taken

	try
	{
		UsersCacheManager::getInstance()->getFromNickname(newNick);
		newNickIsOk = false;
	}
	catch (UserCacheException &ignored)
	{}

	//TODO: Check if the nickname is banned from the channel

	//std::vector<Channel *> inChannels = user->getChannelList();
	//for (std::vector<Channel *>::iterator it = inChannels.begin(); it != inChannels.end(); it++)
	//{
//		Channel *channel = *it;
	//	std::list<User *> bannedUsers = channel->getBannedUsers();
//	}

	//TODO: Check if the nickname is censorred


	//if (StringUtils::hasCensuredWord(newNick, Server::getCensoredWords()).first)
	//{
	//	std::string bannedMessage = "Sorry, this nickname is banned from this server";
	//	sendServerReply(incomingFD, ERR_YOUREBANNED(user->getNickname(), bannedMessage), RED, BOLDR);
	//	return ;
	//}
}