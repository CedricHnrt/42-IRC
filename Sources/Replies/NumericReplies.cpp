//
// Created by pgouasmi on 4/12/24.
//

#include "NumericReplies.hpp"

void sendServerReply(int const fd, std::string buffer)
{
	if (send(fd, buffer.c_str(), buffer.length(), 0) == -1)
		std::cout << "send KO" << std::endl;

}
