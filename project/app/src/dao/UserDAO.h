//
// Created by matias on 4/24/16.
//

#ifndef TINDER_SERVER_USERDAO_H
#define TINDER_SERVER_USERDAO_H

#include "../model/User.h"
#include <list>
#include <DBConnector.h>
#include <SharedConnector.h>

/**
 * @class UserDAO
 * Provides methods to access the information of the users.
 *
 * @author MLuraschi.
 */
class UserDAO {
public:
	/**
	* Default constructor. Deleting both connectors should be done by the caller.
	*/
	UserDAO(SharedConnector* shared, DBConnector* db);

	virtual ~UserDAO();

	/**
	* Gets from the connector the user with the received ID. It returns a pointer to it. If the user is not found it
	* returns NULL. Deleting the User* is responsibility of the caller.
	*
	* @param id of the username to get.
	*/
	User *getUserById(int id);

	/**
	* Gets all the users stored in the shared server. It returns a list of all the users.
	* Deleting the users is responsibility of the caller.
	*/
	list<User *> getAllUsers();

	/**
	* Given a user it uploads it as a new user to the shared server. It also sets the id of the user
	* with the one given by the Shared Server. It returns true or false if the Post was successful.
	*
	* @param user to upload to the shared server. Modification of the Id is in place.
	*/
	bool saveNewUser(User *user);

	/**
	 * It deletes the user with the given ID from the shared server.
	 *
	 * @param id of the user to delete.
	 */
	bool deleteUserByID(int id);

	/**
	 * It gets all the interests saved in the shared server.
	 */
	unordered_map<string, set<string>> getInterests();

	/**
	 * It saves the new interest to the shared server.
	 *
	 * @param category category to append the new value to. If it does not exist, it is created.
	 * @param value to add to the category.
	 */
	bool saveNewInterest(string category, string value);

	/**
	* Given a user it uploads the changes in the profile to the shared server. It returns true or false if the
	* put was successful.
	*
	* @param user to upload the changes from.
	*/
	bool updateUserProfile(User *user);

	/**
	 * Given a username and password combination, it returns true if the combination matches an entry in the DB
	 *
	 * @param username username to look for in the db.
	 * @param password password that has to be in the username account.
	 */
	bool validateUsernamePassword(std::string username, std::string password);

	/**
	 * It checks if the username received is already in the db.
	 *
	 * @param username username to look for in the DB.
	 */
	bool isUsernameTaken(std::string username);

	/**
	 * Changes the password for the user. Returns true if th change was successful. If the current password does not
	 * match or the username does not exists it throws an exception.
	 *
	 * @param username to change the password from.
	 * @param currentPassword current password of the username that wants to change it.
	 * @param new Password password that the username wants to have.
	 */
	bool changePasswordForUser(std::string username, std::string currentPassword,std::string newPassword);

	/**
	 * Creates a new user with the received password. If the username is taken it throws an exception.
	 *
	 * @param username to create.
	 * @param password to set to the username.
	 */
	bool saveNewUsername(std::string username, std::string password);


private:
	DBConnector* dbConnector;
	SharedConnector* sharedConnector;


	/**
	 * Given a Json, it returns all the users contained in it. The caller must delete de users after using them.
	 *
	 * @param root Json object to look for the users.
	 */
	list<User *> assembleUsersFromJson(Json::Value &root);

};


#endif //TINDER_SERVER_USERDAO_H
