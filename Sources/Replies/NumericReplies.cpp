//
// Created by pgouasmi on 4/12/24.
//

#include "NumericReplies.hpp"

void sendServerReply(int const fd, std::string buffer, int color, std::string mode)
{
//	std::cout << "buffer: " << buffer << std::endl;
	if (color != -1)
	{
		std::ostringstream digit;
		digit<<color;
		std::string scolor = "\x03";
		scolor += digit.str();


		buffer.insert(buffer.find(':', 2) + 1, scolor);
	}
	if (!mode.empty())
	{
		buffer.insert(buffer.find(':', 2) + 1, mode);
		buffer.insert(buffer.length() - 2, mode);
	}
	if (send(fd, buffer.c_str(), buffer.length(), 0) == -1)
		std::cout << "send KO" << std::endl;
}
