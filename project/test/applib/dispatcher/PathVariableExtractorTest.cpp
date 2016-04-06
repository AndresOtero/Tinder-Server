#include "dispatcher/PathVariableExtractor.h"
#include "PathVariableExtractorTest.h"
#include <string>
using namespace std;


PathVariableExtractorTest::PathVariableExtractorTest() {
}

PathVariableExtractorTest::~PathVariableExtractorTest() {};

void PathVariableExtractorTest::SetUp() {};

void PathVariableExtractorTest::TearDown() {};

TEST_F(PathVariableExtractorTest, ExtractParamsOK) {
	string format = "/api/v1/#name#/#lastname#";
	string uri = "/api/v1/julio/roca";
	PathVariableExtractor pve ( format, uri );
	string name = pve.get("name");
	string lastname= pve.get("lastname");
	string expectedname = "julio";
	string expectedlastname = "roca";
	ASSERT_STREQ(expectedname.c_str(), name.c_str());
	ASSERT_STREQ(expectedlastname.c_str(), lastname.c_str());
}

TEST_F(PathVariableExtractorTest, ByDefaultBazFalseIsFalse) {
	ASSERT_TRUE(true);
}

TEST_F(PathVariableExtractorTest, SometimesBazFalseIsTrue) {
	ASSERT_TRUE(true);
}

