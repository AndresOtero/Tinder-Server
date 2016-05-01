//
// Created by jonathan on 30/04/16.
//

#include "AuthenticationDAO.h"


bool AuthenticationDAO::isUsernameTaken(string username) {
	return  this->dbConnector.exist(username);

}

void AuthenticationDAO::saveUser(string username, string password) {
	this->dbConnector.putValueInKey(username, password);
}

string AuthenticationDAO::getPassword(string username) {
	return this->dbConnector.getValueForKey(username);
}

AuthenticationDAO::AuthenticationDAO(DBConnector &dbConnector) : dbConnector(dbConnector) { }