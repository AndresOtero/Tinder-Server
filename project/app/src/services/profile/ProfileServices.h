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

using namespace std;

class ProfileServices {
public:
	ProfileServices(SharedConnector* connector);
	virtual ~ProfileServices();
	User* getUserByID(int id);
	list<User *> getAllUsers();
	list<User *> assembleUsersFromJson(Json::Value &root); //No usar, es public para tests.
	bool updateUserProfile(User* user);
	Json::Value assembleJsonFromUser(User* user);
	bool saveNewUser(User* user);
	bool deleteUserByID(int id);

private:
	bool getAllUsers(Json::Value& usersData);
	bool getUserByID(int id, Json::Value& userData);
	SharedConnector* connector;

};

#endif /* SRC_PROFILESERVICES_H_ */
