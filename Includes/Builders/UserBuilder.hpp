#ifndef USERBUILDER_HPP
	#define USERBUILDER_HPP
	#include <string>
	#include <vector>
	#include "User.hpp"
	#include "UserProperties.hpp"
/**
 * @class UserBuilder
 * @brief A builder class for creating User objects.
 * @author jbadaire
 *
 * This class provides a way to construct User objects in a step-by-step manner.
 * It includes setter methods for each property of the User class, and a build method
 * to finally create the User object.
 */
	class UserBuilder
	{
		private:
			std::string userName;
			std::string realName;
			std::string nickname;
			std::string ipAddr;
			int userSocketFd;
			size_t uniqueId;
			UserProperties properties;
			std::vector<std::string> connectionInfos;

			bool isComplete;
			std::string password;
			std::string inBuffer;

		public:
			UserBuilder();

			/**
			 * @brief Sets the name of the User.
			 * @param name The name to set.
			 * @return A reference to the UserBuilder object.
			 * @author jbadaire
			 */
			UserBuilder &setName(const std::string &name);

			/**
			 * @brief Sets the real name of the User.
			 * @param realName The real name to set.
			 * @return A reference to the UserBuilder object.
			 * @author jbadaire
			 */
			UserBuilder &setRealName(const std::string &realName);

			/**
			 * @brief Sets the nickname of the User.
			 * @param nickname The nickname to set.
			 * @return A reference to the UserBuilder object.
			 * @author jbadaire
			 */
			UserBuilder &setNickname(const std::string &nickname);

			/**
			 * @brief Sets the IP address of the User.
			 * @param ipAddr The IP address to set.
			 * @return A reference to the UserBuilder object.
			 * @author jbadaire
			 */
			UserBuilder &setIpAddr(const std::string &ipAddr);

			/**
			 * @brief Sets the socket ID of the User.
			 * @param userSocketFd The socket ID to set.
			 * @return A reference to the UserBuilder object.
			 * @author jbadaire
			 */
			UserBuilder &setUserSocketId(int userSocketFd);

			/**
			 * @brief Sets the properties of the User.
			 * @param properties The properties to set.
			 * @return A reference to the UserBuilder object.
			 * @author jbadaire
			 */
			UserBuilder &setProperties(const UserProperties &properties);

			/**
			 * @brief Clears the builder for reuse.
			 * @author jbadaire
			 */
			void clearBuilder();

			/**
			 * @brief Builds the User object.
			 * @return A reference to the built User object.
			 * @throws UserBuildException if essentials properties for IRC are invalid.
			 * @author jbadaire
			 */
			User &build();

			UserBuilder &fillBuffer(const std::string data, int incomingFD);

			bool 	isBuilderComplete();
	};
#endif
