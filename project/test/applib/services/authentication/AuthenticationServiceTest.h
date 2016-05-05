#include <DBConnector.h>
#include <AuthenticationDAO.h>
#include <SharedConnector.h>
#include <ProfileServices.h>
#include <AuthenticationService.h>
#include "gtest/gtest.h"

static const char *const DB_FILE = "/tmp/usersTestDB";
static const char *const DB_FILE2 = "/tmp/profilesTestDB";
static const char *const DB_FILE3 = "/tmp/transTestDB";

// The fixture for testing class Foo.
class AuthenticationServiceTest : public ::testing::Test {


protected:

    // You can do set-up work for each test here.
    AuthenticationServiceTest();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~AuthenticationServiceTest();

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();

    DBConnector * connector;
    DBConnector * profileConnector;
    DBConnector * transConnector;
    AuthenticationDAO * authDAO;
    SharedConnector * sharedConnector;
    ProfileServices * profileService;
    TranslationDAO * transDAO;

    UserDAO * userDAO;
    AuthenticationService * service;
};