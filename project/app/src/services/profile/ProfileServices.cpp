#include <iostream>
#include "ProfileServices.h"
#include "../../log/Logger.h"
#include "UserNotFoundException.h"

ProfileServices::ProfileServices(UserDAO* dao) {
	this->dao = dao;
}

ProfileServices::~ProfileServices() {}


User* ProfileServices::getUserByID(int id){
	//TODO ESTO NO DEBERÍA SEGUIR EXISTIENDO
	User* user = this->dao->getUserById(id);
	if(!user) {
		LOG_ERROR << "Error getting user with ID: " << to_string(id);
		//throw UserNotFoundException(id);
	}
	return user;
}


list<User *> ProfileServices::getAllUsers() {
	return this->dao->getAllUsers();
}


void ProfileServices::deleteUserByID(int id) {
	//TODO ESTO NO DEBERÍA EXISTIR TAMPOCO NO MANEJAMOS IDS ARRIBA, ADEMAS NO VAMOS A ESTAR BORRANDO USERS DESDE ESTA APP, O SI?
	if (!this->dao->deleteUserByID(id)) {
		LOG_ERROR << "Error deleting user con ID: " << to_string(id);
//		throw UserNotFoundException(id);
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

void ProfileServices::addInterest(string userid, string category, string value) {
	//TODO MATY TIENE TU NOMBRE ESTO
}

unordered_map<string, set<string>> ProfileServices::searchInterest(string query) {
	//TODO tiene que buscar entre todos los intereses por categoria o valor.
	unordered_map<string, set<string>> result;
	return result;
}

void ProfileServices::removeInterest(string userid, string category, string value) {
	//TODO tiene que remover un interes de la lista de usuarios.
}

User *ProfileServices::getUserByID(string id) {
	return nullptr;
}



