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

}