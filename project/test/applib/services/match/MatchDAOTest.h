//
// Created by matias on 4/16/16.
//

#ifndef TINDER_SERVER_MATCHDAOTEST_H
#define TINDER_SERVER_MATCHDAOTEST_H

static const char *const DB_FILE = "/tmp/testsMatch";

#include "gtest/gtest.h"

class MatchDAOTest : public ::testing::Test{

protected:

	// You can do set-up work for each test here.
	MatchDAOTest();

	// You can do clean-up work that doesn't throw exceptions here.
	virtual ~MatchDAOTest();

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	// Code here will be called immediately after the constructor (right
	// before each test).
	virtual void SetUp();

	// Code here will be called immediately after each test (right
	// before the destructor).
	virtual void TearDown();

	DBConnector * connector;
	MatchDAO * dao;
};


#endif //TINDER_SERVER_MATCHDAOTEST_H
