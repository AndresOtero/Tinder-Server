//
// Created by matias on 5/26/16.
//

#ifndef TINDER_SERVER_INTERESTTEST_H
#define TINDER_SERVER_INTERESTTEST_H

#include <gtest/gtest.h>

class InterestTest : public ::testing::Test{
public:
	InterestTest();
	virtual ~InterestTest();

	// Code here will be called immediately after the constructor (right
	// before each test).
	virtual void SetUp();

	// Code here will be called immediately after each test (right
	// before the destructor).
	virtual void TearDown();
};


#endif //TINDER_SERVER_INTERESTTEST_H
