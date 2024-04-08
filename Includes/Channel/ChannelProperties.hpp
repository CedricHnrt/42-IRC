#ifndef CHANNELPROPERTIES_HPP
	#define CHANNELPROPERTIES_HPP

	#include <list>
	class Channel;

	class ChannelProperties {
		private:
			std::list<size_t> usersInChannel;
			std::list<size_t> mutedUsers;
			std::list<size_t> bannedUsers;
			std::list<size_t> invited;
			std::list<size_t> operators;

		public:
			bool containsChannel(std::list<size_t> list, Channel& target);
			bool addChannelToList(std::list<size_t> list, Channel& target);
			bool removeChannelFromList(std::list<size_t> list, Channel& target);

			std::list<size_t> getUsersInChannel();
			std::list<size_t> getMutedUsers();
			std::list<size_t> getBannedUsers();
			std::list<size_t> getInvited();
			std::list<size_t> getOperators();
	};

#endif
