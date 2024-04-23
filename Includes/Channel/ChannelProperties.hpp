#ifndef CHANNELPROPERTIES_HPP
	#define CHANNELPROPERTIES_HPP
	#include <list>
	#include <map>
	#include <string>

	#include "ChannelExceptions.hpp"
	#include "User.hpp"

//canal modes
#define TOPIC 't'
#define NOEXTRENALMESSAGES 'n'
#define SECRET 's'
#define INVITEONLY 'i'
#define MODERATED 'm'
#define KEY 'k'
#define PRIVATE 'p'

//user modes
#define OPERATOR 'o'
#define VOICE 'v'
#define BAN 'b'
#define AWAY 'a'
#define INVISIBLE 'i'

#include <stdlib.h>

	class ChannelProperties {
		private:
			std::list<size_t> usersInChannel;
			std::list<size_t> mutedUsers;
			std::list<size_t> bannedUsers;
			std::list<size_t> invited;
			std::list<size_t> operators;

			std::string canalModes;
			std::string topic;
			bool hasPassword;
			std::string password;
			std::map<size_t, std::string> userModes;

		public:
			std::list<size_t> getUsersInChannel();
			std::list<size_t> getMutedUsers();
			std::list<size_t> getBannedUsers();
			std::list<size_t> getInvited();
			std::list<size_t> getOperators();

			bool doesChannelHaveMode(char c) const;
			bool doesUserHaveMode(size_t UserId, char c) const throw (ChannelGetException);
			void addModeToChannel(size_t callingUserId, char c) throw (ChannelGetException);
			void addModeToUser(size_t targetId, size_t callingUserId, char c) throw (ChannelGetException);
			void addUserToChannel(size_t userId);

			std::string &getPassword();
			void setPassword(const std::string &newPassword);
			bool isPasswordSet() const;
			void setPasswordStatus(bool value);

			std::string &getTopic();
			void setTopic(size_t userId, const std::string &newTopic);


	};

#endif
