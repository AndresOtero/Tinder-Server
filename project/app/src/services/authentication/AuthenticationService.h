/*
 * AuthenticationService.h
 *
 *  Created on: Mar 21, 2016
 *      Author: matias
 */

#ifndef SRC_AUTHENTICATIONSERVICE_H_
#define SRC_AUTHENTICATIONSERVICE_H_

 #include <string>
 #include "db/DBConnector.h"

class AuthenticationService {
public:
	AuthenticationService(DBConnector* connector);
	virtual ~AuthenticationService();
	bool isLoginValid(std::string username, std::string password);
	bool isUsernameTaken(std::string username);
	bool changePasswordForUser(std::string username, std::string password);

private:
	DBConnector* connector;
};

#endif /* SRC_AUTHENTICATIONSERVICE_H_ */
