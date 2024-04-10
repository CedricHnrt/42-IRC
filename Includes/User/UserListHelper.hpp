#ifndef USERLISTHELPER_HPP
#define USERLISTHELPER_HPP
	#include <list>
	#include "User.hpp"

	/**
	 * @class UserListManager
	 * @brief A manager class for handling a list of User objects.
	 *
	 * This class provides methods for managing a list of User objects,
	 * including adding, removing, and checking if a User is in the list.
	 *
	 * @author jbadaire
	 */
	class UserListManager
	{
		private:
			std::list<User> userList;

		public:
			/**
			 * @brief Adds a User to the list.
			 * @param user The User to add.
			 * @return true if the User was added successfully, false otherwise.
			 * @author jbadaire
			 */
			bool addUser(const User &user);

			/**
			 * @brief Removes a User from the list.
			 * @param user The User to remove.
			 * @return true if the User was removed successfully, false otherwise.
			 * @author jbadaire
			 */
			bool removeUser(const User &user);

			/**
			 * @brief Checks if a User is in the list.
			 * @param user The User to check.
			 * @return true if the User is in the list, false otherwise.
			 * @author jbadaire
			 */
			bool containsUser(const User &user);
	};
#endif
