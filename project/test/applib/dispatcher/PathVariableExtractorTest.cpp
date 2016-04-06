#include "dispatcher/PathVariableExtractor.h"
#include "PathVariableExtractorTest.h"
#include "dispatcher/PathVariableException.h"
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

TEST_F(PathVariableExtractorTest, WrongPath) {
	string format = "/api/v1/#name#/#lastname#";
	string uri = "/api/v1/julio";
    try {

    	PathVariableExtractor pve ( format, uri );
        FAIL() << "Expected std::PathVariableException";
    }
    catch(PathVariableException const & err) {
        EXPECT_EQ(err.what(),std::string(uri + " doesn't match with " + format) );
    }
	ASSERT_TRUE(true);
}

TEST_F(PathVariableExtractorTest, SometimesBazFalseIsTrue) {
	ASSERT_TRUE(true);
}

