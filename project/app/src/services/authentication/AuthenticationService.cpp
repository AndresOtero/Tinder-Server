#include <Logger.h>
#include "AuthenticationService.h"

AuthenticationService::AuthenticationService(UserDAO* dao) {
	this->dao = dao;
}

AuthenticationService::~AuthenticationService() {}

bool AuthenticationService::isLoginValid(std::string username, std::string password) {
	return this->dao->validateUsernamePassword(username, password);
}

bool AuthenticationService::isUsernameTaken(std::string username) {
	return this->dao->isUsernameTaken(username);
}

bool AuthenticationService::changePasswordForUser(std::string username, std::string currentPassword,std::string newPassword){
	if (currentPassword == newPassword) {
		LOG_ERROR << "Current password and new password can not be the same.";
		throw AuthenticationException("Current Password and new password received are the same.");
	}
	return this->dao->changePasswordForUser(username, currentPassword, newPassword);
}


bool AuthenticationService::saveNewUser(std::string username, std::string password) {
	return this->dao->saveNewUsername(username, password);
}


