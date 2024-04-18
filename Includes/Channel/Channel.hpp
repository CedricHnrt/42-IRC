#ifndef CHANNEL_HPP
	#define CHANNEL_HPP

	#include <string>
	#include <vector>
	#include "ChannelProperties.hpp"

	class User;

	class Channel {

		private:
			std::string name;
			size_t uniqueId;
			std::string topic;
			std::string password;
			ChannelProperties properties;
			std::vector<User *> _usersInChannel;
			Channel();
		public:
			std::string getName() const;
			std::string getTopic() const;
			std::string getPassword() const;
			size_t getUniqueId() const;
			ChannelProperties getProperties() const;
			void addUserToChannel(User *user);
			std::vector<User *> getChannelsUsers() const;
			User *getUserByName(const std::string &name);
		private:
			friend class ChannelCacheManager;
			friend class ChannelBuilder;
			void setName(const std::string& name);
			void setTopic(const std::string& topic);
			void setPassword(const std::string& password);
			void setUniqueId(size_t uniqueId);
			void setProperties(const ChannelProperties& properties);

	};

#endif
