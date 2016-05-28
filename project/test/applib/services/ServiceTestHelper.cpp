//
// Created by jonathan on 28/05/16.
//

#include "ServiceTestHelper.h"
#include <boost/filesystem.hpp>


ServiceTestHelper::ServiceTestHelper() {
    boost::filesystem::remove_all(DB_AUTH);
    boost::filesystem::remove_all(DB_TRANSLATION);
    this->authDAO = nullptr;
    this->authenticationDB = nullptr;
    this->sharedConnector = nullptr;
    this->translationDAO = nullptr;
    this->translationDB = nullptr;
    this->userDAO = nullptr;
}

void ServiceTestHelper::buildUserDAO() {
    this->sharedConnector = new SharedConnector(URL_SHARED);
    this->userDAO = new UserDAO(this->sharedConnector);
}



void ServiceTestHelper::buildAuthDAO() {
    this->authenticationDB = new DBConnector(DB_AUTH);
    this->authDAO = new AuthenticationDAO(*this->authenticationDB);
}

void ServiceTestHelper::buildTranslationDAO() {
    this->translationDB = new DBConnector(DB_TRANSLATION);
    this->translationDAO = new TranslationDAO(*this->translationDB);
}

UserDAO * ServiceTestHelper::getUsersDAO() {
    if(this->userDAO == nullptr) buildUserDAO();
    return this->userDAO;
}


TranslationDAO *ServiceTestHelper::getTranslationDAO() {
    if(this->translationDAO == nullptr) this->buildTranslationDAO();
    return this->translationDAO;
}

AuthenticationDAO *ServiceTestHelper::getAuthenticationDAO() {
    if(this->authDAO == nullptr ) buildAuthDAO();
    return this->authDAO;
}


ServiceTestHelper::~ServiceTestHelper() {
    if(userDAO != nullptr) delete userDAO;
    if(sharedConnector != nullptr) delete sharedConnector;
    if(translationDAO != nullptr) delete translationDAO;
    if(translationDB != nullptr) delete translationDB;
    if(authenticationDB != nullptr) delete authenticationDB;
    if(authDAO != nullptr) delete authDAO;
    boost::filesystem::remove_all(DB_AUTH);
    boost::filesystem::remove_all(DB_TRANSLATION);
}

DBConnector *ServiceTestHelper::getTranslationDB() {
    if(this->translationDAO == nullptr) this->buildTranslationDAO();
    return this->getTranslationDB();
}

DBConnector *ServiceTestHelper::getAuthenticationDB() {
    if(this->authDAO == nullptr ) buildAuthDAO();
    return this->authenticationDB;
}



