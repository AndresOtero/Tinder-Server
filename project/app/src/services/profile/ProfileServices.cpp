#include <iostream>
#include <TranslationException.h>
#include "ProfileServices.h"
#include "../../log/Logger.h"
#include "UserNotFoundException.h"

ProfileServices::ProfileServices(UserDAO *dao, TranslationDAO *transDao) {
	this->dao = dao;
	this->translationDAO = transDao;
}

ProfileServices::~ProfileServices() {}


User* ProfileServices::getUserByID(int id){
	User* user = this->dao->getUserById(id);
	if(!user) {
		LOG_ERROR << "Error getting user with ID: " << to_string(id);
		throw UserNotFoundException( to_string(id));
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

User *ProfileServices::getUserByID(string id) {
    int externalId = translateId(id);

    return dao->getUserById(externalId);;
}

int ProfileServices::translateId(string id) {
    try {
         return translationDAO->get(id);
    } catch (TranslationException  & e) {
        this->reloadMapping();
        try {
            return translationDAO->get(id);
        } catch (TranslationException & e) {
            //if fail again, cannot get user.
            throw UserNotFoundException(id);
        }
    }
}

void ProfileServices::reloadMapping() {
    const list<User *> users = dao->getAllUsers();
    for(auto iterator = users.begin(); iterator != users.end(); ++iterator) {
        User * user = *iterator;
        translationDAO->save(user->getId(), user->getExternalId());
        delete user;
    }
}






