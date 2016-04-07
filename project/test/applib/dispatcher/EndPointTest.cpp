#include "EndPointTest.h"

#include "dispatcher/EndPoint.h"
#include "dispatcher/NoSuchMethodHandlerException.h"
using ::testing::NiceMock;
using ::testing::_;

EndPointTest::EndPointTest() {
//	EndPoint ep ("asdas", );
}

EndPointTest::~EndPointTest() {
	delete callmock;
};



void EndPointTest::SetUp() {
	this->callmock = new VoidCallerConcrete();
	voidHandler = [this] (WebContext& wc){
		this->callmock->call(0);
	};
};

void EndPointTest::TearDown() {};

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

	EXPECT_CALL(*callmock,call(_)).Times(0);
}


TEST_F(EndPointTest, ByDefaultBazFalseIsFalse) {
	ASSERT_TRUE(true);
}

TEST_F(EndPointTest, SometimesBazFalseIsTrue) {
	ASSERT_TRUE(true);
}


