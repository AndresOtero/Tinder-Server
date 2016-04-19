//
// Created by matias on 4/18/16.
//

#include "ChatServices.h"


ChatServices::ChatServices(ChatDAO *chatDao, MatchDAO* matchDao) {
	this->chat = chatDao;
	this->match = matchDao;
}

ChatServices::~ChatServices() { }

bool ChatServices::sendMessageFromTo(string from, string fromid, string to, string toid) {
	return false;
}

Json::Value ChatServices::getConversationBetweenUsers(string userA, string idA, string userB, string idB) {
	return Json::Value();
}

