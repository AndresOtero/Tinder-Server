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


list<User *> ProfileServices::getAllUsers() {
    try {
        return this->dao->getAllUsers();
    } catch (ConnectionException & e) {
        LOG_ERROR << LOG_PREFIX << "Error listing users: " << e.what();
        throw ServiceException(e.what());
    }

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

        //if is registered
        User * storedUser = this->getUserByID(user->getId());
        user->setExternalId(storedUser->getExternalId());
        //mantengo sincronizado el email.
        user->setEmail(user->getId());
        this->dao->updateUser(user);
        delete storedUser;

    } catch (UserNotFoundException &e) {
        //if not registered
        this->translationDAO->remove(user->getId());
        user->setEmail(user->getId());
        this->dao->saveNewUser(user);
        this->translationDAO->save(user->getId(), user->getExternalId());
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


void ProfileServices::saveInterests(string userid, list <Interest> &interests) {
    User * user = nullptr;
    try {
        user = this->getUserByID(userid);
        user->removeInterests();
        for (list<Interest>::iterator it = interests.begin(); it != interests.end(); ++it) {
            Interest ints = *it;
            user->addInterest(ints.getCategory(), ints.getValue());
        }

        this->saveOrUpdateProfile(user);
    } catch (ConnectionException & e) {
        LOG_ERROR << LOG_PREFIX << "Connection error: " << e.what();
        if(user != nullptr)  delete user;
        throw ServiceException(e.what());
    } catch(ServiceException &e) {
          if(user != nullptr)  delete user;
        throw e;
    };
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
        try {
            return dao->getUserById(externalId);;
        } catch (ConnectionException & e) {
            LOG_ERROR << LOG_PREFIX << "Connection error: " << e.what();
            throw ServiceException(e.what());
        }

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
            throw UserNotFoundException(id);
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

void ProfileServices::updateLocation(string username, double latitude, double longitude) {
    User * user = this->getUserByID(username);
    user->setLongitude(longitude);
    user->setLatitude(latitude);
    this->saveOrUpdateProfile(user);
    delete user;
}

void ProfileServices::deleteUserByID(string id) {
    int translated = this->translateId(id, false);
    this->deleteUserByID(translated);
    this->translationDAO->remove(id);
}









