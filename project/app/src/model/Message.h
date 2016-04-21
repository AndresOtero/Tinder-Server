//
// Created by matias on 4/20/16.
//

#ifndef TINDER_SERVER_MESSAGE_H
#define TINDER_SERVER_MESSAGE_H


#include "User.h"
#include <ctime>

class Message {
public:
	Message(string content, User* sender, User* receiver);
	Message(string content, tm* savedTime, User* sender, User* receiver);
	virtual ~Message();
	User* getSender();
	User* getReceiver();
	string getContent();
	tm* getTime();

private:
	struct tm currentTime;
	string content;
	User* sender;
	User* receiver;
};


#endif //TINDER_SERVER_MESSAGE_H
