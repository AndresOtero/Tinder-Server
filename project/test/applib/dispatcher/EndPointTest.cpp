#include "EndPointTest.h"

#include "dispatcher/EndPoint.h"
#include "dispatcher/NoSuchMethodHandlerException.h"
using ::testing::NiceMock;
using ::testing::_;

EndPointTest::EndPointTest() {
}

EndPointTest::~EndPointTest() {

};



void EndPointTest::SetUp() {
	this->callmock = new VoidCallerConcrete();
	voidHandler = [this] (WebContext& wc){
		this->callmock->call();
	};
};

void EndPointTest::TearDown() {
	delete callmock;
};

TEST_F(EndPointTest, NotMatchNoNextToDispatch) {
	EndPoint ep ("//////////", this->voidHandler);
	http_message hm;
	hm.uri = mg_mk_str("/uri");
	hm.method = mg_mk_str("POST");
	RestRequest req(&hm);

	RestResponse rep;
	try {
		ep.handle(req , rep);
        FAIL() << "Expected std::PathVariableException";
    }
    catch(NoSuchMethodHandlerException  const & err) {
        EXPECT_EQ(err.what(),std::string("Handler for POST: /uri not found"));
    }

	EXPECT_CALL(*callmock,call()).Times(0);
}


TEST_F(EndPointTest, handle) {
	EndPoint ep ("/uri/#user#", this->voidHandler);
	http_message hm;
	hm.uri = mg_mk_str("/uri/juan");
	hm.method = mg_mk_str("GET");
	RestRequest req(&hm);
	RestResponse rep;
	EXPECT_CALL(*callmock,call()).Times(1);
	ep.handle(req , rep);

}

TEST_F(EndPointTest, SometimesBazFalseIsTrue) {
	ASSERT_TRUE(true);
}


