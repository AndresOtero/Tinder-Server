#include "AuthenticationServiceTest.h"
#include "services/authentication/AuthenticationService.h"


AuthenticationServiceTest::AuthenticationServiceTest() {};

AuthenticationServiceTest::~AuthenticationServiceTest() {};

void AuthenticationServiceTest::SetUp() {};

void AuthenticationServiceTest::TearDown() {};

TEST_F(AuthenticationServiceTest, ValidateUsernamePassword) {
	DBConnector connector("/tmp/usersTestDB");
	UserDAO dao(nullptr, &connector);
	AuthenticationService service(&dao);
	std::string usuario = "username";
	std::string password = "pass";
	ASSERT_FALSE(service.isUsernameTaken(usuario));
	ASSERT_FALSE(service.isLoginValid(usuario, password));

	bool resultado = connector.putValueInKey(usuario, password);
	ASSERT_TRUE(resultado);

	ASSERT_TRUE(service.isLoginValid(usuario, password));
	ASSERT_TRUE(service.isUsernameTaken(usuario));

	connector.deleteKey(usuario);
}

TEST_F(AuthenticationServiceTest, ChangeUsernamePassword) {
	DBConnector connector("/tmp/usersTestDB");
	UserDAO dao(nullptr, &connector);
	AuthenticationService service(&dao);
	std::string usuario = "username";
	std::string password = "pass";

	bool resultado = connector.putValueInKey(usuario, password);
	ASSERT_TRUE(resultado);

	ASSERT_TRUE(service.isLoginValid(usuario, password));

	std::string newPass = "nueva";
	resultado = service.changePasswordForUser(usuario, password,newPass);
	ASSERT_TRUE(resultado);
	ASSERT_FALSE(service.isLoginValid(usuario, password));
	ASSERT_TRUE(service.isLoginValid(usuario, newPass));
	ASSERT_ANY_THROW(service.changePasswordForUser(usuario, "caca", newPass));
	connector.deleteKey(usuario);
}

TEST_F(AuthenticationServiceTest, saveNewUser) {
	DBConnector connector("/tmp/usersTestDB");
	UserDAO dao(nullptr, &connector);
	AuthenticationService service(&dao);
	std::string usuario = "username";
	std::string password = "pass";

	bool resultado = service.saveNewUser(usuario, password);
	ASSERT_TRUE(resultado);
	ASSERT_TRUE(service.isLoginValid(usuario, password));
	ASSERT_ANY_THROW(service.saveNewUser(usuario, password));
	connector.deleteKey(usuario);
}