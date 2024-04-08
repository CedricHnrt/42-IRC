#ifndef USERPROPERTIES_HPP
	#define USERPROPERTIES_HPP
	#include <list>
	#include "../Channel/Channel.hpp"

	class User;
	class UserProperties
	{
		private:
			bool isAway;
			std::list<size_t> joinedChannels;
			std::list<size_t> notifiedConnectionUsers;
			std::list<size_t> ignoreUsers;
			std::list<size_t> blockedUsers;
			std::list<std::string> permissions;
		public:
			UserProperties();
			void setAway(bool away);
			bool getAway() const;

			void joinChannel(Channel channel);
			void leaveChannel(Channel channel);

			std::list<std::string> getPermissions();
			void addPermission(std::string permission);
			void removePermission(std::string permission);
			bool hasPermission(const std::string& permission);

			bool containsUser(std::list<size_t> list, User& target);
			bool addTargetToList(std::list<size_t> list, User& target);
			bool removeTargetFromList(std::list<size_t> list, User& target);

			std::list<size_t> getIgnoredUsers();
			std::list<size_t> getBlockedUsers();
			std::list<size_t> getJoinedChannels();
			std::list<size_t> getNotifiedConnectionUsers();
	};


#endif
