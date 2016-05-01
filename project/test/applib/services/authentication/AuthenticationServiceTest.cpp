#include "AuthenticationServiceTest.h"
#include "services/authentication/AuthenticationService.h"
#include <boost/filesystem.hpp>

AuthenticationServiceTest::AuthenticationServiceTest() {};

AuthenticationServiceTest::~AuthenticationServiceTest() {};

void AuthenticationServiceTest::SetUp() {
	boost::filesystem::remove_all(DB_FILE);
	this->connector = new DBConnector(DB_FILE);
};

void AuthenticationServiceTest::TearDown() {
	delete this->connector;
	boost::filesystem::remove_all(DB_FILE);
};

TEST_F(AuthenticationServiceTest, ValidateUsernamePassword) {

	AuthenticationDAO dao(*connector);
	AuthenticationService service(&dao);
	std::string usuario = "username";
	std::string password = "pass";
	ASSERT_FALSE(service.isLoginValid(usuario, password));
	service.saveNewUser(usuario, password);
	ASSERT_TRUE(service.isLoginValid(usuario, password));
}

TEST_F(AuthenticationServiceTest, ChangeUsernamePassword) {

	AuthenticationDAO dao(*connector);
	AuthenticationService service(&dao);
	std::string usuario = "username";
	std::string password = "pass";

	connector->putValueInKey(usuario, password);

	ASSERT_TRUE(service.isLoginValid(usuario, password));

	std::string newPass = "nueva";
	service.changePassword(usuario,
									   password,
									   newPass);

	ASSERT_FALSE(service.isLoginValid(usuario, password));
	ASSERT_TRUE(service.isLoginValid(usuario, newPass));
	ASSERT_ANY_THROW(service.changePassword(usuario,password,
											newPass));
}

TEST_F(AuthenticationServiceTest, saveNewUser) {

	AuthenticationDAO dao(*connector);
	AuthenticationService service(&dao);
	std::string usuario = "username";
	std::string password = "pass";

	service.saveNewUser(usuario, password);

	ASSERT_TRUE(service.isLoginValid(usuario, password));

}