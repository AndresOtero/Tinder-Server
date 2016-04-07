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

bool AuthenticationService::changePasswordForUser(std::string username, std::string password) {
	//Si el usuario no existe lo agrega. Para crear un nuevo usuario usar primero isUsernameTaken()
	return (connector->putValueInKey(username, password));
}
