#include "JsonWebTokenTest.h"
#include "JsonWebToken.h"
#include <string>
#include "json/json/json.h"
#include <time.h>
#include <iostream>

JsonWebTokenTest::JsonWebTokenTest() {};

JsonWebTokenTest::~JsonWebTokenTest() {};

void JsonWebTokenTest::SetUp() {};

void JsonWebTokenTest::TearDown() {};

TEST_F(JsonWebTokenTest, EncodeAndDecodeUsername) {
	struct tm * timeinfo;
	time_t rawtime;
	time ( &rawtime );
	timeinfo = localtime(&rawtime);
	timeinfo->tm_hour++;
	if (timeinfo->tm_hour > 23) {
		timeinfo->tm_hour = 0;
	}
	std::string expTime(asctime (timeinfo));
	JsonWebToken generator;
	std::string token = generator.generateTokenForUser("matias");
	Json::Value decoded;
	bool resultado = generator.getUsernameFromToken(token, decoded);
	ASSERT_TRUE(resultado);
	ASSERT_TRUE(decoded.get("name", "ERROR").asString() == "matias");
	ASSERT_TRUE(decoded.get("iss", "ERROR").asString() == "Tinder2-Shared");
	std::string vencimiento = decoded.get("exp", "ERROR").asString();
	ASSERT_TRUE( vencimiento == expTime);
}
