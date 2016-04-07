/*
 * ApiDispatcherTest.h
 *
 *  Created on: 7 de abr. de 2016
 *      Author: jonathan
 */

#ifndef TEST_APPLIB_DISPATCHER_APIDISPATCHERTEST_H_
#define TEST_APPLIB_DISPATCHER_APIDISPATCHERTEST_H_
#include "gtest/gtest.h"
#include "dispatcher/ApiDispatcher.h"
#include "VoidCallerMock.h"
#include <functional>
using namespace std;

class ApiDispatcherTest: public ::testing::Test  {
protected:
	function<void(WebContext&)> defaultHandler;
	VoidCallerConcrete * defaultInvoked;
	ApiDispatcher * dispatcher;
public:
	ApiDispatcherTest();
    virtual void SetUp();
    virtual void TearDown();
	virtual ~ApiDispatcherTest();
};

#endif /* TEST_APPLIB_DISPATCHER_APIDISPATCHERTEST_H_ */
