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
	RestRequest req(NULL);
	RestResponse rep;
	WebContext context(req, rep, pv);
	string value = "parametro";
	ASSERT_STREQ(value.c_str(), context.getParam("param1").c_str());


}