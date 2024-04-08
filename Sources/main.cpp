#include "Server.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Error: Usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}
	try
	{
		Server server(argv[1], argv[2]);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}



