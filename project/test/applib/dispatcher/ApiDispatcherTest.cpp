/*
 * ApiDispatcherTest.cpp
 *
 *  Created on: 7 de abr. de 2016
 *      Author: jonathan
 */

#include "ApiDispatcherTest.h"
#include "dispatcher/ApiDispatcher.h"

ApiDispatcherTest::ApiDispatcherTest() {
	// TODO Auto-generated constructor stub

}

void ApiDispatcherTest::SetUp() {
}

ApiDispatcherTest::~ApiDispatcherTest() {
	// TODO Auto-generated destructor stub
}



TEST_F(ApiDispatcherTest, DispatchWithoutConfiguration) {
	http_message hm;
	hm.uri = mg_mk_str("/uri/juan");
	hm.method = mg_mk_str("GET");
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
