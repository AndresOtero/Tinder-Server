//
// Created by matias on 5/4/16.
//

#ifndef TINDER_SERVER_PROFILESERVICESTEST_H
#define TINDER_SERVER_PROFILESERVICESTEST_H

#include <gtest/gtest.h>
#include "ProfileServices.h"
class ProfileServicesTest : public ::testing::Test{
protected:

	// You can do set-up work for each test here.
	ProfileServicesTest();

	// You can do clean-up work that doesn't throw exceptions here.
	virtual ~ProfileServicesTest();

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	// Code here will be called immediately after the constructor (right
	// before each test).
	virtual void SetUp();

	// Code here will be called immediately after each test (right
	// before the destructor).
	virtual void TearDown();


	ProfileServices * service;
	ServiceTestHelper
};


#endif //TINDER_SERVER_MATCHSERVICESTEST_H
