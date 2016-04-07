/*
 * ApiDispatcherTest.cpp
 *
 *  Created on: 7 de abr. de 2016
 *      Author: jonathan
 */

#include "ApiDispatcherTest.h"
#include "dispatcher/ApiDispatcher.h"
#include "dispatcher/NoSuchMethodHandlerException.h"
#include "gmock/gmock.h"
using ::testing::NiceMock;
using ::testing::_;

ApiDispatcherTest::ApiDispatcherTest() {
	defaultInvoked= 0;
	dispatcher = 0;
}

void ApiDispatcherTest::SetUp() {
	this->defaultInvoked = new VoidCallerConcrete();
	defaultHandler = [this] (WebContext& wc){
		this->defaultInvoked->call();
	};
	dispatcher = new ApiDispatcher();
	dispatcher->registerEndPoint(RestRequest::GET, "/api/v1/#username#", this->defaultHandler);
}

void ApiDispatcherTest::TearDown() {
	delete defaultInvoked;
	delete dispatcher;
}

ApiDispatcherTest::~ApiDispatcherTest() {
	// TODO Auto-generated destructor stub
}



TEST_F(ApiDispatcherTest, DispatchWithoutConfiguration) {
	http_message hm;
	hm.uri = mg_mk_str("/uri/juan");
	hm.method = mg_mk_str("POST");
	ApiDispatcher dispatcher;
	RestRequest req(&hm);
	RestResponse rep;
	try {
		//EXPECT_CALL(*callmock,call()).Times(0);
		dispatcher.handle(req, rep);
        FAIL() << "Expected std::NoSuchMethodHandlerException";
    }
    catch(NoSuchMethodHandlerException  const & err) {
        EXPECT_EQ(err.what(),std::string("Handler for POST: /uri/juan not found"));
    }
}
TEST_F(ApiDispatcherTest, DispatchOKey) {
	http_message hm;
	hm.uri = mg_mk_str("/api/v1/juan");
	hm.method = mg_mk_str("GET");
	RestRequest req(&hm);
	RestResponse rep;
	EXPECT_CALL(*defaultInvoked,call()).Times(1);
	dispatcher->handle(req, rep);
}


TEST_F(ApiDispatcherTest, defaultError) {
	http_message hm;
	hm.uri = mg_mk_str("/////");
	hm.method = mg_mk_str("PUT");
	RestRequest req(&hm);
	RestResponse rep;
	try {
		//EXPECT_CALL(*callmock,call()).Times(0);
		dispatcher->handle(req, rep);
        FAIL() << "Expected std::NoSuchMethodHandlerException";
    }
    catch(NoSuchMethodHandlerException  const & err) {
        EXPECT_EQ(err.what(),std::string("Handler for PUT: ///// not found"));
    }
}

