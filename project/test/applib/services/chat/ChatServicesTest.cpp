// Created by matias on 4/19/16.
//

#include <ChatDAO.h>
#include <MatchDAO.h>
#include <ChatServices.h>
#include "ChatServicesTest.h"

ChatServicesTest::ChatServicesTest() { }

ChatServicesTest::~ChatServicesTest() { }

void ChatServicesTest::SetUp(){ }

void ChatServicesTest::TearDown() { }

TEST_F(ChatServicesTest, sendMessageToNotLikedPerson) {
	DBConnector chatConnector("/tmp/chattest");
	DBConnector dbConnector("/tmp/matchtest");
	ChatDAO chat(&chatConnector);
	MatchDAO match(&dbConnector);
	ChatServices service(&chat, &match);
	Location location;
	unordered_map<string, set<string>> intereses;
	User userA(1, "caca", "matias", "", "M", 18,"", intereses, location);
	User userB(2, "caca", "maria", "", "F", 18,"", intereses, location);
	Message msg("prueba", &userA, &userB);
	ASSERT_FALSE(service.sendMessageFromTo(&msg));
	match.saveLike(&userA, &userB);
	ASSERT_FALSE(service.sendMessageFromTo(&msg));
	dbConnector.deleteKey("matias:1");
}

TEST_F(ChatServicesTest, sendMessageToLikedPerson) {
	DBConnector chatConnector("/tmp/chattest");
	DBConnector dbConnector("/tmp/matchtest");
	ChatDAO chat(&chatConnector);
	MatchDAO match(&dbConnector);
	ChatServices service(&chat, &match);
	Location location;
	unordered_map<string, set<string>> intereses;
	User userA(1, "caca", "matias", "", "M", 18,"", intereses, location);
	User userB(2, "caca", "maria", "", "F", 18,"", intereses, location);
	Message msg("prueba", &userA, &userB);
	match.saveLike(&userA, &userB);
	match.saveLike(&userB, &userA);
	ASSERT_TRUE(service.sendMessageFromTo(&msg));
	chatConnector.deleteKey("matias:1-maria:2");
	dbConnector.deleteKey("matias:1");
	dbConnector.deleteKey("maria:2");
}


