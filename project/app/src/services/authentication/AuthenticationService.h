/*
 * AuthenticationService.h
 *
 *  Created on: Mar 21, 2016
 *      Author: matias
 */

#ifndef SRC_AUTHENTICATIONSERVICE_H_
#define SRC_AUTHENTICATIONSERVICE_H_

 #include <string>
 #include "../../db/DBConnector.h"

/**
 * @class AuthenticationService
 *
 * Provides functionality to authenticate a user.
 *
 * @author MLuraschi
 */

//TODO HABRÍA QUE TENER UN TIPO DE EXCEPCION, ESTOS METODOS NO TIENEN QUE DEVOLVER TRUE O FALSE, SINO UNA EXCEPCIÓN
//CON SU ERROR, PARA PODER DEVOLVER ALGO DE INFO AL FRONTEND
class AuthenticationService {
public:
	/**
	 * Default constructor
	 *
	 * @param connector The DBConnector that has the users DB opened.
	 */
	AuthenticationService(DBConnector* connector);
	virtual ~AuthenticationService();

	/**
	 * Returns true if the combination of username and password provided match.
	 *
	 * @param username to check if exists.
	 * @param password to check if is the one the username has.
	 */
	bool isLoginValid(std::string username, std::string password);

	/**
	 * Returns true if there is an entry with that username in the DB.
	 *
	 * @param username to check if it already exists.
	 */
	bool isUsernameTaken(std::string username);

	/**
	 * Changes the password for the user. Returns true if th change was succesful.
	 *
	 * @param username to change the password from.
	 * @param password to set to the username.
	 */
	bool changePasswordForUser(std::string username, std::string password);

private:
	/**
	 * Connector to the database
	 *
	 * @see DBConnector
	 */
	DBConnector* connector;
};

#endif /* SRC_AUTHENTICATIONSERVICE_H_ */
