#ifndef CHANNELMANAGER_HPP
#define CHANNELMANAGER_HPP

	#include "Channel.hpp"
	#include <list>

	class ChannelCacheManager
	{
		private:
			static ChannelCacheManager* instance;
			std::list<Channel> channels;
			size_t uniqueIdCounter;
			ChannelCacheManager();

		public:
			void addToCache(Channel& channel);
			Channel& getFromCache(size_t uniqueId);
			void deleteFromCache(size_t uniqueId);
			std::list<Channel> getCache();
			static ChannelCacheManager* getInstance();
	};


#endif
