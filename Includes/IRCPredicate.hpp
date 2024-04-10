#ifndef COMPARATOR_HPP
	#define COMPARATOR_HPP
	#include "Channel.hpp"
	#include "User.hpp"

	class ChannelPredicate
	{
		private:
			size_t channelId;
		public:
			explicit ChannelPredicate(size_t channelId);
			bool operator () (Channel channel);
			bool operator == (size_t channelID);
	};

	class UserPredicate
	{
			private:
				size_t userId;
			public:
				explicit UserPredicate(size_t userId);
				bool operator () (User user);
				bool operator == (size_t userId);
	};
#endif
