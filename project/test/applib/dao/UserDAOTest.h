//
// Created by matias on 4/25/16.
//

#ifndef TINDER_SERVER_USERDAOTEST_H
#define TINDER_SERVER_USERDAOTEST_H


#include <gtest/gtest.h>

class UserDAOTest : public ::testing::Test {

	// You can do set-up work for each test here.
	UserDAOTest();

	// You can do clean-up work that doesn't throw exceptions here.
	virtual ~UserDAOTest();

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	// Code here will be called immediately after the constructor (right
	// before each test).
	virtual void SetUp();

	// Code here will be called immediately after each test (right
	// before the destructor).
	virtual void TearDown();
};


#endif //TINDER_SERVER_USERDAOTEST_H
