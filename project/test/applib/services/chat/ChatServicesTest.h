//
// Created by matias on 4/19/16.
//

#ifndef TINDER_SERVER_CHATSERVICESTEST_H
#define TINDER_SERVER_CHATSERVICESTEST_H


#include <gtest/gtest.h>

class ChatServicesTest : public ::testing::Test{

public:
	ChatServicesTest();
	virtual ~ChatServicesTest();

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	// Code here will be called immediately after the constructor (right
	// before each test).
	virtual void SetUp();

	// Code here will be called immediately after each test (right
	// before the destructor).
	virtual void TearDown();
};


#endif //TINDER_SERVER_CHATSERVICESTEST_H
