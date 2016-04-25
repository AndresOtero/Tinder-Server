#include "AuthenticationService.h"

AuthenticationService::AuthenticationService(DBConnector* connector) {
	this->connector = connector;
}

AuthenticationService::~AuthenticationService() {}

bool AuthenticationService::isLoginValid(std::string username, std::string password) {
	std::string value;
	if (!connector->getValueForKey(username, value)) return false;
	if (value != password) return false;
	return true;
}

bool AuthenticationService::isUsernameTaken(std::string username) {
	std::string value;
	return (connector->getValueForKey(username, value));
}

bool AuthenticationService::changePasswordForUser(std::string username, std::string currentPassword,std::string newPassword){
	if (!this->isLoginValid(username, currentPassword)) {
		throw AuthenticationException("Combination of username and password invalid.");
	}
	return (this->connector->putValueInKey(username, newPassword));
}


bool AuthenticationService::saveNewUser(std::string username, std::string password) {
	if (this->isUsernameTaken(username)) {
		throw AuthenticationException("Username " + username + " already exists.");
	}
	return this->connector->putValueInKey(username, password);
}


