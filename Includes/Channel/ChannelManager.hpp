#ifndef CHANNELMANAGER_HPP
#define CHANNELMANAGER_HPP

	#include <list>
	#include "Channel.hpp"

	class ChannelManager
	{
		private:
			std::list<Channel> channels;
			size_t uniqueIdCounter;
			static ChannelManager* instance;
			ChannelManager() : uniqueIdCounter(0) {}

		public:
			void publishChannel(Channel& channel);
			Channel& getChannel(size_t uniqueId);
			bool channelExists(size_t uniqueId);
			void deleteChannel(size_t uniqueId);
			std::list<Channel> getChannels();
			static ChannelManager* getInstance();
	};


#endif
