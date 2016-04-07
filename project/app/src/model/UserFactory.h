/*
 * User.h
 *
 *  Created on: Apr 1, 2016
 *      Author: matias
 */

#ifndef SRC_USERFACTORY_H_
#define SRC_USERFACTORY_H_

#include "sharedConnector/SharedConnector.h"
#include "User.h"
#include <list>

using namespace std;

class UserFactory {
public:
	UserFactory(SharedConnector* connector);
	virtual ~UserFactory();
	User* getUserByID(int id);
	list<User *> getAllUsers();
	list<User *> assembleUsersFromJson(Json::Value &root); //No usar, es public para tests.

private:
	bool getAllUsers(Json::Value& usersData);
	bool getUserByID(int id, Json::Value& userData);
	SharedConnector* connector;

};

#endif /* SRC_USERFACTORY_H_ */
