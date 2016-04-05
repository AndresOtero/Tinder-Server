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
	PathVariableExtractor pve ("/api/v1/[name]/[lastname]", "api/v1/julio/roca");
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

