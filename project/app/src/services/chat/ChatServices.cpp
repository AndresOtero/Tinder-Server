//
// Created by matias on 4/18/16.
//

#include "ChatServices.h"


ChatServices::ChatServices(ChatDAO *chatDao, MatchDAO* matchDao) {
	this->chat = chatDao;
	this->match = matchDao;
}

ChatServices::~ChatServices() { }

bool ChatServices::sendMessageFromTo(string from, string to) {
	return false;
}

Json::Value ChatServices::getConversationBetweenUsers(string userA, string userB) {
	return Json::Value();
}

