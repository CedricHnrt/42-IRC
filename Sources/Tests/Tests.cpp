#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Channel.hpp"
#include "ChannelCacheManager.hpp"
#include "User.hpp"
#include "UserBuilder.hpp"
#include "ChannelBuilder.hpp"

TEST_SUITE("CHANNELS")
{
	TEST_CASE("Channel Tests")
	{
		ChannelCacheManager *channelManager = ChannelCacheManager::getInstance();
		ChannelBuilder builder;
		builder.setName("Channel1").setTopic("Channel1 Description").setPassword("Channel1 Password");
		Channel channel1 = builder.build();
		builder.setName("Channel2").setTopic("Channel2 Description").setPassword("Channel2 Password");
		Channel channel2 = builder.build();
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

		SUBCASE("Channel Manager")
		{
			channelManager->addToCache(channel1);
			channelManager->addToCache(channel2);

			CHECK(channelManager->getCache().size() == 2);
			CHECK(channelManager->getFromCache(channel1.getUniqueId()).getName() == "Channel1");
			CHECK(channelManager->getFromCache(channel2.getUniqueId()).getName() == "Channel2");
			channelManager->deleteFromCache(channel1.getUniqueId());
			CHECK(channelManager->getCache().size() == 1);
			CHECK_THROWS(channelManager->getFromCache(channel1.getUniqueId()));
			CHECK_NOTHROW(channelManager->getFromCache(channel2.getUniqueId()));
			channelManager->deleteFromCache(channel2.getUniqueId());
			CHECK(channelManager->getCache().size() == 0);
		}
	}
}

TEST_SUITE("BUILDERS")
{
	TEST_CASE("User Builder Tests")
	{
		UserBuilder builder;

		SUBCASE("Good user")
		{
			builder.setName("Jimmy").setNickname("vSKAH").setRealName("BLA");
			builder.setIpAddr("127.0.0.1").setUserSocketId(10);
			User goodUser = builder.build();
			CHECK(goodUser.getName() == "Jimmy");
			CHECK(goodUser.getNickname() == "vSKAH");
			CHECK(goodUser.getRealName() == "BLA");
			CHECK(goodUser.getIpAddr() == "127.0.0.1");
			CHECK(goodUser.getUserSocketId() == 10);
			CHECK_THROWS(builder.build());
		}

		SUBCASE("Missing name")
		{
			builder.setNickname("vSKAH").setRealName("BLA");
			builder.setIpAddr("127.0.0.1").setUserSocketId(10);
			CHECK_THROWS(builder.build());
		}

		SUBCASE("Missing realName")
		{
			builder.setName("Jimmy").setNickname("vSKAH");
			builder.setIpAddr("127.0.0.1").setUserSocketId(10);
			CHECK_THROWS(builder.build());
		}

		SUBCASE("Missing nickname")
		{
			builder.setName("Jimmy").setRealName("BLA");
			builder.setIpAddr("127.0.0.1").setUserSocketId(10);
			CHECK_THROWS(builder.build());
		}

		SUBCASE("Missing Socket Id")
		{
			builder.setName("Jimmy").setNickname("vSKAH").setRealName("BLA");
			builder.setIpAddr("127.0.0.1");
			CHECK_THROWS(builder.build());
		}
	}
}





