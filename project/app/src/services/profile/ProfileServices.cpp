#include <iostream>
#include "ProfileServices.h"
#include "../../log/Logger.h"
#include "UserNotFoundException.h"

ProfileServices::ProfileServices(UserDAO* dao) {
	this->dao = dao;
}

ProfileServices::~ProfileServices() {}


User* ProfileServices::getUserByID(int id){
	User* user = this->dao->getUserById(id);
	if(!user) {
		LOG_ERROR << "Error getting user with ID: " << to_string(id);
		throw UserNotFoundException(to_string(id));
	}
	return user;
}


list<User *> ProfileServices::getAllUsers() {
	return this->dao->getAllUsers();
}


void ProfileServices::deleteUserByID(int id) {
	if (!this->dao->deleteUserByID(id)) {
		LOG_ERROR << "Error deleting user con ID: " << to_string(id);
		throw UserNotFoundException(to_string(id));
	}
	LOG_INFO << "User with ID: " << to_string(id) << " deleted.";
	return;
}

void ProfileServices::updateUserProfile(User* user) {
	if (!this->dao->updateUserProfile(user)) {
		LOG_ERROR << "Error update user with id: " << user->getId();
		throw UserNotFoundException(user->getId());
	}
	return;
}

bool ProfileServices::saveNewUser(User* user) {
	if (!this->dao->saveNewUser(user)) {
				LOG_ERROR << "Error haciendo post del user nuevo";
		return false;
	}
	return true;
}


unordered_map<string, set<string>> ProfileServices::getInterests() {
	return this->dao->getInterests();
}

bool ProfileServices::saveNewInterest(string category, string value) {
	if (!this->dao->saveNewInterest(category, value)) {
		LOG_ERROR << "Error haciendo post del interest nuevo";
		return false;
	}
	return true;
}


