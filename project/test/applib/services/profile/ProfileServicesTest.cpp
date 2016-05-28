//
// Created by matias on 5/4/16.
//

#include <boost/filesystem.hpp>
#include <UserNotFoundException.h>
#include "ServiceException.h"
#include "ProfileServicesTest.h"
#include "list"
using namespace std;

ProfileServicesTest::ProfileServicesTest() {
    this->helper = new ServiceTestHelper();
    this->service = new ProfileServices(this->helper->getUsersDAO(), this->helper->getTranslationDAO());
}

ProfileServicesTest::~ProfileServicesTest() {
    delete helper;
    delete service;

}

void ProfileServicesTest::SetUp() {
    unordered_map<string, set<string>> interests;
    user1 = new User(USER_ID_1,
                          "Nombre", 0,
                          USER_ID_1,
                          "M", 21, "", interests, Location(12, 12));

    this->helper->getUsersDAO()->saveNewUser(user1);

}

void ProfileServicesTest::TearDown() {
    this->helper->getUsersDAO()->deleteUserByID(user1->getExternalId());
    delete user1;
}

TEST_F(ProfileServicesTest, getAll) {
    unordered_map<string, set<string>> interests;
    User *user2 = new User(USER_ID_2,
                           "Nombre", 0,
                           USER_ID_2,
                           "M", 21, "", interests, Location(12, 12));

    this->helper->getUsersDAO()->saveNewUser(user2);

    std::list<User *> users = this->service->getAllUsers();
    bool user1Found = false;
    bool user2Found = false;

    for (std::list<User *>::iterator it = users.begin(); it != users.end() ; ++it ) {
            if((*it)->getId() == user1->getId()){
                user1Found = true;

            }
            if((*it)->getId() == user2->getId()) user2Found = true;
    }

    this->helper->getUsersDAO()->deleteUserByID(user2->getExternalId());
    delete user2;

    ASSERT_TRUE(user1Found);
    ASSERT_TRUE(user2Found);


}

TEST_F(ProfileServicesTest, saveNewUser) {
    unordered_map<string, set<string>> interests;
    User *user = new User(USER_ID_2,
                          "Nombre", 0,
                          USER_ID_2,
                          "M", 21, "", interests, Location(12, 12));
    this->service->saveOrUpdateProfile(user);

    std::list<User *> users = this->service->getAllUsers();
    bool user1Found = false;
    for (std::list<User *>::iterator it = users.begin(); it != users.end() ; ++it ) {
        if((*it)->getId() == user->getId()){
            user1Found = true;
        }
    }

    this->helper->getUsersDAO()->deleteUserByID(user->getExternalId());
    delete user;
    ASSERT_TRUE(user1Found);

}


TEST_F(ProfileServicesTest, updateUser) {

    user1->setName("Nombre2");
    this->service->saveOrUpdateProfile(user1);

    string nameFound = "";
    std::list<User *> users = this->service->getAllUsers();
    bool user1Found = false;
    for (std::list<User *>::iterator it = users.begin(); it != users.end() ; ++it ) {
        if((*it)->getId() == user1->getId()){
            user1Found = true;
            nameFound = user1->getName();
        }
    }

    ASSERT_EQ("Nombre2", nameFound);
    ASSERT_TRUE(user1Found);
}


TEST_F(ProfileServicesTest, updateLocation) {

    this->service->updateLocation(USER_ID_1, 100, 200);

    User *pUser = this->service->getUserByID(USER_ID_1);
    double lat = pUser->getLatitude();
    double longi = pUser->getLongitude();
    delete pUser;
    ASSERT_EQ(lat, 100);
    ASSERT_EQ(longi, 200);
}

TEST_F(ProfileServicesTest, getUserById) {
    User * userFound = this->service->getUserByID(USER_ID_1);
    string nameFound = userFound->getName();
    delete userFound;
    ASSERT_EQ(nameFound, "Nombre");
}


TEST_F(ProfileServicesTest, getInexistentUser) {
    ASSERT_THROW(this->service->getUserByID(USER_ID_2), UserNotFoundException);
}

TEST_F(ProfileServicesTest, updateInterests) {
    list<Interest> newInterests;
    newInterests.push_back(Interest("futbol", "river"));
    newInterests.push_back(Interest("futbol", "river"));
    newInterests.push_back(Interest("futbol", "independiente"));
    newInterests.push_back(Interest("comida", "pizza"));


    this->service->saveInterests(USER_ID_1, newInterests);

    User * userFound = this->service->getUserByID(USER_ID_1);
    list <Interest> list = userFound->getInterests();
    delete userFound;

    ASSERT_EQ(3, list.size());

}

TEST_F(ProfileServicesTest, listInterests) {

    unordered_map<string, set<string>> interestsMap = this->service->getInterests();
    ASSERT_TRUE(interestsMap.size() > 1);

}



TEST_F(ProfileServicesTest, deleteUser) {
    unordered_map<string, set<string>> interests;
    User *user2 = new User(USER_ID_2,
                           "Nombre", 0,
                           USER_ID_2,
                           "M", 21, "", interests, Location(12, 12));

    this->service->saveOrUpdateProfile(user2);
    delete user2;
    user2 = this->service->getUserByID(USER_ID_2);
    //user exists.
    delete user2;


    this->service->deleteUserByID(USER_ID_2);

    ASSERT_THROW(this->service->getUserByID(USER_ID_2), UserNotFoundException);

}


TEST_F(ProfileServicesTest, sharedDown) {

    SharedConnector * shc = new SharedConnector("http://unaurl.com");
    UserDAO * userDAO = new UserDAO(shc);
    this->helper->getTranslationDAO()->save(USER_ID_1, 47);
    ProfileServices * pf = new ProfileServices(userDAO, this->helper->getTranslationDAO());
    ASSERT_THROW(pf->getAllUsers(), ServiceException);
    ASSERT_THROW(pf->deleteUserByID(USER_ID_1), ServiceException);

    ASSERT_THROW(pf->saveOrUpdateProfile(user1), ServiceException);
    ASSERT_THROW(pf->getInterests(), ServiceException);

    list<Interest> newInterests;
    newInterests.push_back(Interest("futbol", "river"));
    ASSERT_THROW(pf->saveInterests(USER_ID_1, newInterests), ServiceException);
    ASSERT_THROW(pf->getUserByID(USER_ID_1), ServiceException);

}
