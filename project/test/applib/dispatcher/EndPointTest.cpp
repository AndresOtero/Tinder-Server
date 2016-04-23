#include "EndPointTest.h"

#include "dispatcher/EndPoint.h"
#include "dispatcher/NoSuchMethodHandlerException.h"
using ::testing::NiceMock;
using ::testing::_;

EndPointTest::EndPointTest() {
	callmock= 0;
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

	EndPoint ep("//////////", filter,this->voidHandler);
	http_message hm;
	hm.uri = mg_mk_str("/uri");
	hm.method = mg_mk_str("DELETE");
	RestRequest req(&hm);

	RestResponse rep;
	try {
		EXPECT_CALL(*callmock,call()).Times(0);
		ep.handle(req , rep);
        FAIL() << "Expected NoSuchMethodHandlerException";
    }
    catch(NoSuchMethodHandlerException  const & err) {
        EXPECT_EQ(err.what(),std::string("Handler for DELETE: /uri not found"));
    }

}


TEST_F(EndPointTest, Handle) {
	EndPoint ep("/uri/#user#", filter, this->voidHandler);
	http_message hm;
	hm.uri = mg_mk_str("/uri/juan");
	hm.method = mg_mk_str("GET");
	RestRequest req(&hm);
	RestResponse rep;
	EXPECT_CALL(*callmock,call()).Times(1);
	ep.handle(req , rep);

}

TEST_F(EndPointTest, HandledByNext) {
	EndPoint ep("//////////", filter, this->voidHandler);
	VoidCallerConcrete caller;
	function<void(WebContext&)> otherHandler = [&caller](WebContext& wc){
		caller.call();
	};
	EndPoint * 	ep2 = new EndPoint("/uri/#user#", filter, otherHandler);
	ep.setNext(ep2);
	http_message hm;
	hm.uri = mg_mk_str("/uri/juan");
	hm.method = mg_mk_str("GET");
	RestRequest req(&hm);
	RestResponse rep;
	EXPECT_CALL(*callmock,call()).Times(0);
	EXPECT_CALL(caller,call()).Times(1);

	ep.handle(req , rep);
}

TEST_F(EndPointTest, HandledByNextNext) {
	EndPoint ep("//////////", filter, this->voidHandler);
	VoidCallerConcrete caller;
	function<void(WebContext&)> otherHandler = [&caller](WebContext& wc){
		caller.call();
	};
	EndPoint * 	ep2 = new EndPoint("//////////", filter, this->voidHandler);
	EndPoint * 	ep3 = new EndPoint("/uri/#user#", filter, otherHandler);
	ep.setNext(ep2);
	ep.setNext(ep3);
	http_message hm;
	hm.uri = mg_mk_str("/uri/juan");
	hm.method = mg_mk_str("GET");
	RestRequest req(&hm);
	RestResponse rep;
	EXPECT_CALL(*callmock,call()).Times(0);
	EXPECT_CALL(caller,call()).Times(1);
	ep.handle(req , rep);
}


