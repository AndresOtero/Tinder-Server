#include <Logger.h>
#include <AuthenticationDAO.h>
#include <ProfileServices.h>
#include <UserNotFoundException.h>
#include "AuthenticationService.h"

AuthenticationService::AuthenticationService(AuthenticationDAO *dao, ProfileServices  * profileService) {
	this->dao = dao;
	this->profileService = profileService;
}

AuthenticationService::~AuthenticationService() {}

bool AuthenticationService::isLoginValid(std::string username, std::string password) {
	string actual = this->dao->getPassword(username);
	return !(actual != password);
}



void AuthenticationService::changePassword(std::string userid, std::string currentPassword, std::string newPassword) {
	string storedPassword = this->dao->getPassword(userid);
	if(storedPassword != currentPassword){
		LOG_ERROR << "Not match stored password.";
		throw AuthenticationException("Not match stored password");
	}



	if (currentPassword == newPassword) {
		LOG_ERROR << "Current password and new password can not be the same.";
		throw AuthenticationException("Current Password and new password received are the same.");
	}

	this->dao->saveUser(userid, newPassword);
}


bool AuthenticationService::saveNewUser(std::string username, std::string password) {
	if(this->dao->isUsernameTaken(username)) {
		throw AuthenticationException("User Already Exist.");
	}
	this->dao->saveUser(username, password);
	try {
		this->profileService->getUserByID(username);
		return false;
	} catch (UserNotFoundException & e) {
		return true;
	}

}

void AuthenticationService::deleteUser(std::string username, std::string password) {
	if(this->dao->isUsernameTaken(username)) {
		if(this->isLoginValid(username, password)) {
			this->dao->deleteUser(username);
			try {
				this->profileService->deleteUserByID(username);
				LOG_DEBUG << "User profile deleted: " << username;
			} catch (UserNotFoundException & e) {
				LOG_DEBUG << "User profile inexistent: " << username;
			}
		} else {
			throw AuthenticationException("Must be a valid login");
		}

	}

}




