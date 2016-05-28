//
// Created by jonathan on 28/05/16.
//

#ifndef TINDER_SERVER_SERVICETESTHELPER_H
#define TINDER_SERVER_SERVICETESTHELPER_H


#include <SharedConnector.h>
#include <UserDAO.h>
#include <TranslationDAO.h>
#include <AuthenticationDAO.h>

static const char *const DB_AUTH = "/tmp/authTestDB";
static const char *const DB_TRANSLATION = "/tmp/transTestDB";
static const char *const URL_SHARED = "http://tinder-shared.herokuapp.com";


class ServiceTestHelper {
private:

    SharedConnector * sharedConnector;
    UserDAO * userDAO;

    TranslationDAO * translationDAO;
    DBConnector * translationDB;

    AuthenticationDAO * authDAO;
    DBConnector * authenticationDB;


    void buildUserDAO();
    void buildAuthDAO();
    void buildTranslationDAO();
public:
    ServiceTestHelper();
    UserDAO * getUsersDAO();
    TranslationDAO * getTranslationDAO();
    AuthenticationDAO * getAuthenticationDAO();
    DBConnector * getTranslationDB();
    DBConnector * getAuthenticationDB();
    virtual ~ServiceTestHelper();
};


#endif //TINDER_SERVER_SERVICETESTHELPER_H
