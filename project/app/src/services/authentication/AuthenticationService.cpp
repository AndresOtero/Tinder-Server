#include <Logger.h>
#include <AuthenticationDAO.h>
#include "AuthenticationService.h"

AuthenticationService::AuthenticationService(AuthenticationDAO *dao) {
	this->dao = dao;
}

AuthenticationService::~AuthenticationService() {}

bool AuthenticationService::isLoginValid(std::string username, std::string password) {
	string actual = this->dao->getPassword(username);
	return !(actual != password);
}



bool AuthenticationService::changePassword(std::string username, std::string currentPassword, std::string newPassword) {
	string storedPassword = this->dao->getPassword(username);
	if(storedPassword != currentPassword){
		LOG_ERROR << "Not match stored password.";
		throw AuthenticationException("Not match stored password");
	}



	if (currentPassword == newPassword) {
		LOG_ERROR << "Current password and new password can not be the same.";
		throw AuthenticationException("Current Password and new password received are the same.");
	}

	return this->dao->saveUser(username, newPassword);
}


bool AuthenticationService::saveNewUser(std::string username, std::string password) {
	if(this->dao->isUsernameTaken(username)) {
		throw AuthenticationException("User Already Exist.");
	}
	return this->dao->saveUser(username, password);
}


