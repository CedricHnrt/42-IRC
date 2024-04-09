#ifndef COMPARATOR_HPP
	#define COMPARATOR_HPP
	#include <string>
	#include "Channel/Channel.hpp"
	class ChannelPredicate
	{
		private:
			Channel target;
		public:
			explicit ChannelPredicate(const Channel& v);
			bool operator () (const Channel& a);
			bool operator == (const Channel& a);
	};
#endif
