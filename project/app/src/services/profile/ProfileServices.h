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
	 * It deletes the user with the given ID from the shared server. If the user is not found it throws
	 * UserNotFoundException.
	 *
	 * @param id of the user to delete.
	 */
	void deleteUserByID(string id);

	/**
	 * It gets all the interests saved in the shared server.
	 */
	unordered_map<string, set<string>> getInterests();


	/**
	 * Add interest to user
	 * @param userid the user
	 * @param category category of interest
	 * @param value value of interest
	 */
	void saveInterests(string userid, list <Interest> &interests);


	/**
	 * update user location
	 * @param username The username
	 * @param latitude latitude where the user is
	 * @param longitude longitude where the user is
	 *
	 */
	void updateLocation(string username, double latitude, double longitude);



private:
	UserDAO* dao;
	TranslationDAO * translationDAO;
	void reloadMapping();
	int translateId(string id, bool shouldUpdate);
};

#endif /* SRC_PROFILESERVICES_H_ */
