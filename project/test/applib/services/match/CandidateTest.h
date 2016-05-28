//
// Created by matias on 5/26/16.
//

#ifndef TINDER_SERVER_CANDIDATETEST_H
#define TINDER_SERVER_CANDIDATETEST_H

#include <gtest/gtest.h>

class CandidateTest : public ::testing::Test {
public:
	CandidateTest();
	virtual ~CandidateTest();

	// Code here will be called immediately after the constructor (right
	// before each test).
	virtual void SetUp();

	// Code here will be called immediately after each test (right
	// before the destructor).
	virtual void TearDown();

};


#endif //TINDER_SERVER_CANDIDATETEST_H
