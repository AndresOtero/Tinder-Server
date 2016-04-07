#include "dispatcher/EndPoint.h"
#include "EndPointTest.h"

EndPointTest::EndPointTest() {

//	EndPoint ep ("asdas", );
}

EndPointTest::~EndPointTest() {};



void EndPointTest::SetUp() {};

void EndPointTest::TearDown() {};

TEST_F(EndPointTest, ByDefaultBazTrueIsTrue) {
	ASSERT_TRUE(true);
}

TEST_F(EndPointTest, ByDefaultBazFalseIsFalse) {
	ASSERT_TRUE(true);
}

TEST_F(EndPointTest, SometimesBazFalseIsTrue) {
	ASSERT_TRUE(true);
}


