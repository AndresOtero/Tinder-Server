//
// Created by matias on 4/18/16.
//

#include <Logger.h>
#include <AuthenticationException.h>
#include "ChatServices.h"
#include "ChatException.h"


ChatServices::ChatServices(ChatDAO *chatDao, MatchDAO* matchDao) {
	this->chat = chatDao;
	this->match = matchDao;
}

ChatServices::~ChatServices() { }

void ChatServices::sendMessageFromTo(Message *msg) {
	if (!this->match->checkForMatch(msg->getSender(), msg->getReceiver())){
		throw ChatException("Not match found");
	}
	this->chat->saveMsgFromTo(msg);
}

list<Message*>* ChatServices::getConversationBetweenUsers(User* userA, User* userB) {
	std::list<Message*>* lista = new list<Message*>();
	this->chat->getMsgBetween(userA, userB, lista);
	this->chat->getMsgBetween(userB, userA, lista);
	return lista;
}

