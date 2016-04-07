#include "JsonWebTokenTest.h"
#include "services/authentication/JsonWebToken.h"
#include <string>

JsonWebTokenTest::JsonWebTokenTest() {};

JsonWebTokenTest::~JsonWebTokenTest() {};

void JsonWebTokenTest::SetUp() {};

void JsonWebTokenTest::TearDown() {};

TEST_F(JsonWebTokenTest, EncodeAndDecodeUsername) {
	JsonWebToken generator;
	std::string token = generator.generateTokenForUser("matias");
	std::string decoded;
	bool resultado = generator.getUsernameFromToken(token, decoded);
	ASSERT_TRUE(resultado);
	ASSERT_TRUE(decoded == "matias");
}
