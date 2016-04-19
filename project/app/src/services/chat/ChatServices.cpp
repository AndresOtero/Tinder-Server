//
// Created by matias on 4/18/16.
//

#include "ChatServices.h"


ChatServices::ChatServices(ChatDAO *chatDao, MatchDAO* matchDao) {
	this->chat = chatDao;
	this->match = matchDao;
}

ChatServices::~ChatServices() { }

bool ChatServices::sendMessageFromTo(string msg, string from, string fromid, string to, string toid) {
	bool AlikesB = this->match->checkForLike(from, fromid, to, toid);
	bool BlikesA = this->match->checkForLike(to, toid, from, fromid);
	if (!AlikesB || !BlikesA) return false;
	bool saveResult = this->chat->saveMsgFromTo(msg, from, fromid, to, toid);
	return saveResult;
}

Json::Value ChatServices::getConversationBetweenUsers(string userA, string idA, string userB, string idB) {
	return Json::Value();
}

