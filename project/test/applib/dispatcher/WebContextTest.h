/*
 * WebContextTest.h
 *
 *  Created on: 6 de abr. de 2016
 *      Author: jonathan
 */

#ifndef TEST_APPLIB_DISPATCHER_WEBCONTEXTTEST_H_
#define TEST_APPLIB_DISPATCHER_WEBCONTEXTTEST_H_
#include "gtest/gtest.h"


class WebContextTest  : public ::testing::Test {
protected:
	WebContextTest();
    virtual void SetUp();
    virtual void TearDown();
	virtual ~WebContextTest();
};

#endif /* TEST_APPLIB_DISPATCHER_WEBCONTEXTTEST_H_ */
