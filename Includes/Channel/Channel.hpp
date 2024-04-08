#ifndef CHANNEL_HPP
	#define CHANNEL_HPP

	#include <string>
	#include "ChannelProperties.hpp"

	class Channel {

		private:
			std::string name;
			size_t uniqueId;
			std::string topic;
			std::string password;
			ChannelProperties properties;

		public:
			Channel();
			Channel(std::string name, std::string topic, std::string password);
			std::string getName() const;
			std::string getTopic() const;
			std::string getPassword() const;
			size_t getUniqueId() const;

			Channel setName(const std::string& name);
			Channel setTopic(const std::string& topic);
			Channel setPassword(const std::string& password);
			Channel setUniqueId(size_t uniqueId);

	};

#endif
