//
// Created by matias on 5/4/16.
//

#ifndef TINDER_SERVER_MATCHSERVICESTEST_H
#define TINDER_SERVER_MATCHSERVICESTEST_H

static const char *const DB_FILE = "/tmp/testsMatch";

#include <gtest/gtest.h>
#include <MatchDAO.h>
#include <MatchServices.h>

class MatchServicesTest : public ::testing::Test{
protected:

	// You can do set-up work for each test here.
	MatchServicesTest();

	// You can do clean-up work that doesn't throw exceptions here.
	virtual ~MatchServicesTest();

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	// Code here will be called immediately after the constructor (right
	// before each test).
	virtual void SetUp();

	// Code here will be called immediately after each test (right
	// before the destructor).
	virtual void TearDown();

	DBConnector* connector;
	MatchDAO* dao;
	MatchServices* service;

};


#endif //TINDER_SERVER_MATCHSERVICESTEST_H
