//
// Created by matias on 4/19/16.
//

#ifndef TINDER_SERVER_CHATSERVICESTEST_H
#define TINDER_SERVER_CHATSERVICESTEST_H


static const char *const MATCH_DB_FILE = "/tmp/matchtest";

static const char *const CHAT_DB_FILE = "/tmp/chattest";

#include <gtest/gtest.h>
#include <MatchServices.h>

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

	DBConnector * matchDbConnector;
	DBConnector * chatDbConnector;
	ChatDAO * chatDao;
	MatchDAO * matchDao;
	MatchServices* matchServices;

};


#endif //TINDER_SERVER_CHATSERVICESTEST_H
