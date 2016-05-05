/*
 * User.h
 *
 *  Created on: Apr 1, 2016
 *      Author: matias
 */

#ifndef SRC_PROFILESERVICES_H_
#define SRC_PROFILESERVICES_H_

#include "../../sharedConnector/SharedConnector.h"
#include "../../model/User.h"
#include "../../json/json/json.h"
#include <list>
#include <UserDAO.h>
#include <TranslationDAO.h>

using namespace std;

/**
 * @class ProfileServices
 *
 * Provides an interface to get the profile information in the shared server.
 */
class ProfileServices {
public:
	/**
	 * Default constructor
	 *
	 * @param dao UserDao.
	 *
	 */
	ProfileServices(UserDAO *dao, TranslationDAO *transDao);
	virtual ~ProfileServices();


	/**
	 * Asks the DAO to return the User* with the received id. If the user is not found it throws
	 * UserNotFoundException
	 *
	 * @param id of the user to get.
	 */
	User* getUserByID(string id);

	/**
	 * Gets all the users stored in the shared server. It returns a list of all the users.
	 */
	list<User *> getAllUsers();

	/**
	 * Given a user it uploads the changes in the profile to the shared server. It returns true or false if the
	 * put was successful.
	 *
	 * @param user to upload the changes from.
	 */
	void saveOrUpdateProfile(User *user);



	/**
	 * It deletes the user with the given ID from the shared server. If the user is not found it throws
	 * UserNotFoundException.
	 *
	 * @param id of the user to delete.
	 */
	void deleteUserByID(int id);

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
	void saveNewInterest(string category, string value);

	void addInterest(string userid, string category, string value);

	void removeInterest(string userid, string category, string value);

private:
	unordered_map<string, set<string>> populateInterests(Json::Value &root);
	UserDAO* dao;
	TranslationDAO * translationDAO;
	void reloadMapping();

	int translateId(string id, bool shouldUpdate);

	/**
	 * Asks the DAO to return the User* with the received id. If the user is not found it throws
 	* UserNotFoundException
 	*
 	* @param id of the username to get.
 	*/
	User* getUserByID(int id);
};

#endif /* SRC_PROFILESERVICES_H_ */
