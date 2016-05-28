#include "AuthenticationServiceTest.h"
#include "services/authentication/AuthenticationService.h"
#include <boost/filesystem.hpp>

AuthenticationServiceTest::AuthenticationServiceTest() {};

AuthenticationServiceTest::~AuthenticationServiceTest() {};

void AuthenticationServiceTest::SetUp() {
	this->testHelper = new ServiceTestHelper();
	this->profileService = new ProfileServices(this->testHelper->getUsersDAO(), this->testHelper->getTranslationDAO());
	this->service = new AuthenticationService (this->testHelper->getAuthenticationDAO(), this->profileService );
};

void AuthenticationServiceTest::TearDown() {
	delete this->service;
	delete this->profileService;
	delete this->testHelper;
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

	this->testHelper->getAuthenticationDB()->putValueInKey(usuario, password);

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