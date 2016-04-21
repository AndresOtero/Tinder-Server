//
// Created by matias on 4/18/16.
//

#include <Logger.h>
#include "ChatServices.h"


ChatServices::ChatServices(ChatDAO *chatDao, MatchDAO* matchDao) {
	this->chat = chatDao;
	this->match = matchDao;
}

ChatServices::~ChatServices() { }

bool ChatServices::sendMessageFromTo(Message* msg) {
	if (!this->match->checkForMatch(msg->getSender(), msg->getReceiver())) return false;
	bool saveResult = this->chat->saveMsgFromTo(msg);
	return saveResult;
}

list<Message*>* ChatServices::getConversationBetweenUsers(User* userA, User* userB) {
	std::list<Message*>* lista = new list<Message*>();
	this->chat->getMsgBetween(userA, userB, lista);
	this->chat->getMsgBetween(userB, userA, lista);
	return lista;
}

