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
	static User* getUserByID(int id, SharedConnector connector);
	static list<User *> getAllUsers(SharedConnector connector);

};

#endif /* SRC_USERFACTORY_H_ */
