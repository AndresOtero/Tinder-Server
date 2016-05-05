#include <iostream>
#include <TranslationException.h>
#include <ConnectionException.h>
#include <ServiceException.h>
#include "ProfileServices.h"
#include "../../log/Logger.h"
#include "UserNotFoundException.h"

const static string LOG_PREFIX = "ProfileService: ";

ProfileServices::ProfileServices(UserDAO *dao, TranslationDAO *transDao) {
    this->dao = dao;
    this->translationDAO = transDao;
}

ProfileServices::~ProfileServices() { }


User *ProfileServices::getUserByID(int id) {
    User *user = this->dao->getUserById(id);
    if (!user) {
        LOG_ERROR << LOG_PREFIX << "Error getting user with ID: " << to_string(id);
        throw UserNotFoundException(to_string(id));
    }
    return user;
}


list<User *> ProfileServices::getAllUsers() {
    return this->dao->getAllUsers();
}


void ProfileServices::deleteUserByID(int id) {
    try {
        this->dao->deleteUserByID(id);
    } catch (ConnectionException &e) {
        LOG_ERROR << LOG_PREFIX << "Error deleting user con ID: " << to_string(id) << ":  " << e.what();
        throw ServiceException(e.what());
    }


}

void ProfileServices::saveOrUpdateProfile(User *user) {
    try {
        int externalId = this->translateId(user->getId(), true);
        //if is registered
        user->setExternalId(externalId);
        this->dao->updateUser(user);
    } catch (UserNotFoundException &e) {
        //if not registered
        this->dao->saveNewUser(user);
    } catch (ConnectionException &e) {
        LOG_ERROR << LOG_PREFIX << "Connection error: " << e.what();
        throw ServiceException(e.what());
    }

}


unordered_map<string, set<string>> ProfileServices::getInterests() {
    try {
        return this->dao->getInterests();
    } catch (ConnectionException &e) {
        LOG_ERROR << LOG_PREFIX << "Connection error: " << e.what();
        throw ServiceException(e.what());
    }
}

void ProfileServices::saveNewInterest(string category, string value) {
    try {
        this->dao->saveNewInterest(category, value);
    } catch (ConnectionException &e) {
        LOG_ERROR << LOG_PREFIX << "Connection error: " << e.what();
        throw ServiceException(e.what());
    }
}

User *ProfileServices::getUserByID(string id) {
        int externalId;
        try {
            externalId = translateId(id, true);
        } catch (ConnectionException &e) {
            LOG_ERROR << LOG_PREFIX << "Connection error: " << e.what();
            throw ServiceException(e.what());
        } catch (UserNotFoundException &e) {
            LOG_WARNING << LOG_PREFIX << e.what();
            //retry
            this->translationDAO->remove(id);
            throw e;
        }
        return dao->getUserById(externalId);;


}

int ProfileServices::translateId(string id, bool shouldUpdate) {
    try {
        int external =translationDAO->get(id);
        LOG_DEBUG << LOG_PREFIX << "Id translation : " << id << " to " << external;
        return translationDAO->get(id);
    } catch (TranslationException &e) {
        if (shouldUpdate) {


            this->reloadMapping();
            try {
                int external =translationDAO->get(id);
                LOG_DEBUG << LOG_PREFIX << "Id translation : " << id << " to " << external;
                return external;
            } catch (TranslationException &e) {
                //if fail again, cannot get user.
                LOG_DEBUG << LOG_PREFIX << "Id translation not completed to: " << id;
                throw UserNotFoundException(id);
            }
        } else {
            throw e;
        }
    }
}

void ProfileServices::reloadMapping() {
    LOG_INFO << LOG_PREFIX << "Populating translation table";
    const list<User *> users = dao->getAllUsers();
    for (auto iterator = users.begin(); iterator != users.end(); ++iterator) {
        User *user = *iterator;
        translationDAO->save(user->getId(), user->getExternalId());
        delete user;
    }
}






