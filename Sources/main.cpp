#include <Configuration.hpp>

#include "Server.hpp"

int main(int argc, char **argv)
{

	Configuration *configuration = new Configuration("config.conf");
	configuration->load();
	configuration->printSections();
	ConfigurationSection *section = configuration->getSection("SERVER");
	size_t port = section->getNumericValue("port");
	std::cout << "CONFIG PORT: "<< port << std::endl;
	delete configuration;

	if (argc != 3)
	{
		std::cout << "Error: Usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}
	try
	{
		Server server(argv[1], argv[2]);
		server.serverUp();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}



