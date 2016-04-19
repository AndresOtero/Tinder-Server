//
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
	ASSERT_FALSE(service.sendMessageFromTo("prueba", "matias", "1", "maria", "2"));
}

TEST_F(ChatServicesTest, sendMessageToLikedPerson) {
	DBConnector chatConnector("/tmp/chattest");
	DBConnector dbConnector("/tmp/matchtest");
	ChatDAO chat(&chatConnector);
	MatchDAO match(&dbConnector);
	ChatServices service(&chat, &match);
	match.saveLike("matias", "1", "maria", "2");
	match.saveLike("maria", "2", "matias", "1");
	string msg("mensaje de prueba");
	ASSERT_TRUE(service.sendMessageFromTo(msg, "matias", "1", "maria", "2"));
	chatConnector.deleteKey("matias:1-maria:2");
	dbConnector.deleteKey("matias:1");
	dbConnector.deleteKey("maria:2");
}


