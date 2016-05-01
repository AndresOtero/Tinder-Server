//
// Created by jonathan on 30/04/16.
//

#include "AuthenticationDAO.h"


bool AuthenticationDAO::isUsernameTaken(string username) {
	string value;
	return (this->dbConnector.getValueForKey(username, value));
}

bool AuthenticationDAO::saveUser(string username, string password) {
	return this->dbConnector.putValueInKey(username, password);
}

string AuthenticationDAO::getPassword(string username) {
	string value;
	this->dbConnector.getValueForKey(username, value);
	return value;
}

AuthenticationDAO::AuthenticationDAO(DBConnector &dbConnector) : dbConnector(dbConnector) { }