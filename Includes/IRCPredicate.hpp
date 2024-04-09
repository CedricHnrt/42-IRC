#ifndef COMPARATOR_HPP
	#define COMPARATOR_HPP
	#include <string>
	#include "Channel.hpp"
	class ChannelPredicate
	{
		private:
			size_t channelId;
		public:
			explicit ChannelPredicate(size_t channelId);
			bool operator () (Channel channel);
			bool operator == (size_t channelID);
	};
#endif
