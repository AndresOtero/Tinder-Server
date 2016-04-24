/*
 * WebContextTest.cpp
 *
 *  Created on: 6 de abr. de 2016
 *      Author: jonathan
 */

#include "WebContextTest.h"
#include "webserver/RestRequest.h"
#include "webserver/RestResponse.h"
#include "dispatcher/PathVariableExtractor.h"
#include "dispatcher/WebContext.h"
#include "string"
#include "mongoose/mongoose.h"
using namespace std;

WebContextTest::WebContextTest() {
	// TODO Auto-generated constructor stub

}

void WebContextTest::SetUp() {
}

void WebContextTest::TearDown() {
}

WebContextTest::~WebContextTest() {
	// TODO Auto-generated destructor stub
}


TEST_F(WebContextTest, GetParam) {

	PathVariableExtractor pv("/url/#param1#", "/url/parametro") ;
	http_message hm;
	hm.uri = mg_mk_str("/uri");
	hm.header_names[0] = mg_mk_str("");
	RestRequest req(&hm);
	RestResponse rep;
	WebContext context(req, rep, pv);

	EXPECT_TRUE(&req == &(context.getRequest()));
	EXPECT_TRUE(&rep == &(context.getResponse()));
	string value = "parametro";
	ASSERT_STREQ(value.c_str(), context.getParam("param1").c_str());

}

TEST_F(WebContextTest, RequestDescription) {
	ASSERT_STREQ("GET", RestRequest::getDescription(RestRequest::GET).c_str());
	ASSERT_STREQ("POST", RestRequest::getDescription(RestRequest::POST).c_str());
	ASSERT_STREQ("DELETE", RestRequest::getDescription(RestRequest::DELETE).c_str());
	ASSERT_STREQ("PUT", RestRequest::getDescription(RestRequest::PUT).c_str());
	ASSERT_STREQ("", RestRequest::getDescription(RestRequest::UNKNOWN).c_str());
}

