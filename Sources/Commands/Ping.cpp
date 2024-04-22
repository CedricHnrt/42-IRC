/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:57:01 by jbadaire          #+#    #+#             */
/*   Updated: 2024/04/22 15:32:44 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ping.hpp"

#include <string>
#include <TimeUtils.hpp>
#include <iomanip>

Ping::Ping()
{
	this->_name = "Ping";
	this->_description = "Ping to check if alive";
	this->_usage = "/ping [username]";
	this->_permissionLevel = 0;
	this->_expectedArgs.push_back(STRING);
}

void Ping::execute(User *user, Channel *channel, std::vector<std::string> args)
{

	(void)channel;
	(void)user;
	(void)args;

	if (args.size() == 1)
	{
		if (args[0].find("LAG", 0) == std::string::npos)
		{
			const char *firstCharTimestamp = args[0].c_str();
			errno = 0;
			long firstTimeStamp = std::strtol(firstCharTimestamp, NULL, 10);
			if (errno != 0) return;
			std::ostringstream st;

			long secondTimeStamp = TimeUtils::getCurrentTimeMillis();
			double time = (secondTimeStamp - firstTimeStamp) / 1000.0;

			st << std::fixed << std::setprecision(3) << time;

			std::string pongReply = RPL_PING(user->getNickname(), st.str());
			sendServerReply(user->getUserSocketFd(), pongReply, WHITE, DEFAULT);
		}
		else
		{
			long currentTime = TimeUtils::getCurrentTimeMillis();
			user->setLastPingTimestamp(currentTime);
			sendServerReply(user->getUserSocketFd(), ":localhost PONG :" + args[0], -1, DEFAULT);
			std::cout << "pong sent" << std::endl;
		}
	}
	else if (args.size() == 2)
	{

	}


}