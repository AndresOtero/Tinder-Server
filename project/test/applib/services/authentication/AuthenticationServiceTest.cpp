#include "AuthenticationServiceTest.h"
#include "services/authentication/AuthenticationService.h"
#include <boost/filesystem.hpp>

AuthenticationServiceTest::AuthenticationServiceTest() {};

AuthenticationServiceTest::~AuthenticationServiceTest() {};

void AuthenticationServiceTest::SetUp() {
	boost::filesystem::remove_all(DB_FILE);
	boost::filesystem::remove_all(DB_FILE2);
	boost::filesystem::remove_all(DB_FILE3);
	this->connector = new DBConnector(DB_FILE);
	this->profileConnector = new DBConnector(DB_FILE2);
	this->transConnector = new DBConnector(DB_FILE3);
	this->sharedConnector = new SharedConnector("http://tinder-shared.herokuapp.com");

	this->authDAO = new AuthenticationDAO(*this->connector);
	this->userDAO = new UserDAO(this->sharedConnector);
	this->transDAO = new TranslationDAO(*this->transConnector);

	this->profileService = new ProfileServices (this->userDAO, this->transDAO);
	this->service = new AuthenticationService (this->authDAO, this->profileService );
};

void AuthenticationServiceTest::TearDown() {
	delete this->connector;
	delete this->profileConnector;
	delete this->transConnector;
	delete this->sharedConnector;
	delete this->authDAO;
	delete this->userDAO;
	delete this->transDAO;

	delete this->profileService;
	delete this->service;
	boost::filesystem::remove_all(DB_FILE);
	boost::filesystem::remove_all(DB_FILE2);
	boost::filesystem::remove_all(DB_FILE3);
};

TEST_F(AuthenticationServiceTest, ValidateUsernamePassword) {

	std::string usuario = "username";
	std::string password = "pass";
	ASSERT_FALSE(service->isLoginValid(usuario, password));
	service->saveNewUser(usuario, password);
	ASSERT_TRUE(service->isLoginValid(usuario, password));
}

TEST_F(AuthenticationServiceTest, ChangeUsernamePassword) {

	std::string usuario = "username";
	std::string password = "pass";

	connector->putValueInKey(usuario, password);

	ASSERT_TRUE(service->isLoginValid(usuario, password));

	std::string newPass = "nueva";
	service->changePassword(usuario,
									   password,
									   newPass);

	ASSERT_FALSE(service->isLoginValid(usuario, password));
	ASSERT_TRUE(service->isLoginValid(usuario, newPass));
	ASSERT_ANY_THROW(service->changePassword(usuario,password,
											newPass));
}

TEST_F(AuthenticationServiceTest, saveNewUser) {

	std::string usuario = "username";
	std::string password = "pass";

	ASSERT_TRUE(service->saveNewUser(usuario, password));

	ASSERT_TRUE(service->isLoginValid(usuario, password));

}