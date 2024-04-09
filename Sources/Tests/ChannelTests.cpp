#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Includes/Channel/Channel.hpp"
#include "../Includes/Channel/ChannelManager.hpp"

TEST_SUITE("CHANNELS")
{
	TEST_CASE("Channel Tests")
	{
		ChannelManager *channelManager = ChannelManager::getInstance();
		Channel channel1("Channel1", "Channel1 Description", "Channel1 Password");
		Channel channel2("Channel2", "Channel2 Description", "Channel2 Password");

		SUBCASE("Channel Creation")
		{
			CHECK(channel1.getName() == "Channel1");
			CHECK(channel1.getTopic() == "Channel1 Description");
			CHECK(channel1.getPassword() == "Channel1 Password");
			CHECK(channel1.getProperties().getUsersInChannel().size() == 0);

			CHECK(channel2.getName() == "Channel2");
			CHECK(channel2.getTopic() == "Channel2 Description");
			CHECK(channel2.getPassword() == "Channel2 Password");
			CHECK(channel2.getProperties().getUsersInChannel().size() == 0);
		}

		SUBCASE("Channel Publisher")
		{
			channelManager->publishChannel(channel1);
			channelManager->publishChannel(channel2);
			CHECK(channelManager->getChannels().size() == 2);
			CHECK(channelManager->getChannel(channel1.getUniqueId()).getName() == "Channel1");
			CHECK(channelManager->getChannel(channel2.getUniqueId()).getName() == "Channel2");
		}

		SUBCASE("Channel Remover")
		{
			channelManager->deleteChannel(channel1.getUniqueId());
			CHECK(channelManager->getChannels().size() == 1);
			REQUIRE_THROWS(channelManager->getChannel(channel1.getUniqueId()).getName());
			CHECK(channelManager->getChannel(channel2.getUniqueId()).getName() == "Channel2");
		}
	}
}