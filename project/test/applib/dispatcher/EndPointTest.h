#include "gtest/gtest.h"
#include "dispatcher/WebContext.h"
#include <functional>
#include <Filter.h>
#include "VoidCallerMock.h"
using namespace std;


// The fixture for testing class Foo.
class EndPointTest : public ::testing::Test {

protected:
	function<void(WebContext&)> voidHandler;
	VoidCallerConcrete * callmock;
    // You can do set-up work for each test here.
    EndPointTest();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~EndPointTest();

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();

    // The mock bar library shaed by all tests
};
