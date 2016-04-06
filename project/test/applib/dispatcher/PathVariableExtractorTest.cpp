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
	string expectedname = "julio";
	string expectedlastname = "roca";
	string uri = "/api/v1/"+ expectedname+ "/" + expectedlastname;
	PathVariableExtractor pve ( format, uri );
	string name = pve.get("name");
	string lastname= pve.get("lastname");
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
}

TEST_F(PathVariableExtractorTest, PathWithoutParams) {
    	string format = "/api/v1/name/lastname";
    	PathVariableExtractor pve ( format, format );
    	ASSERT_STREQ("", pve.get("name").c_str());
    	ASSERT_STREQ("", pve.get("lastname").c_str());
}

