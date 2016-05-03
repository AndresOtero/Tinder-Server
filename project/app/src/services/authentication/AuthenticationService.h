/*
 * AuthenticationService.h
 *
 *  Created on: Mar 21, 2016
 *      Author: matias
 */

#ifndef SRC_AUTHENTICATIONSERVICE_H_
#define SRC_AUTHENTICATIONSERVICE_H_

#include <string>
#include <UserDAO.h>
#include <AuthenticationDAO.h>
#include "../../db/DBConnector.h"
#include "AuthenticationException.h"

/**
 * @class AuthenticationService
 *
 * Provides functionality to authenticate a user.
 *
 * @author MLuraschi
 */

class AuthenticationService {
public:
	/**
	 * Default constructor
	 *
	 * @param dao dao containing the corresponding db.
	 */
	AuthenticationService(AuthenticationDAO *dao);
	virtual ~AuthenticationService();

	/**
	 * Returns true if the combination of username and password provided match.
	 *
	 * @param username to check if exists.
	 * @param password to check if is the one the username has.
	 */
	bool isLoginValid(std::string username, std::string password);

	/**
	 * Changes the password for the user. Returns true if th change was succesful. If the current password does not
	 * match or the username does not exists it throws an exception.
	 *
	 * @param username to change the password from.
	 * @param currentPassword current password of the username that wants to change it.
	 * @param newPassword password that the username wants to have.
	 */
	void changePassword(std::string username, std::string currentPassword, std::string newPassword);

	/**
	 * Creates a new user with the received password. If the username is taken it throws an exception.
	 *
	 * @param username to create.
	 * @param password to set to the username.
	 */
	void saveNewUser(std::string username, std::string password);

private:

	AuthenticationDAO * dao;
};

#endif /* SRC_AUTHENTICATIONSERVICE_H_ */
