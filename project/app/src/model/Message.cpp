//
// Created by matias on 4/20/16.
//

#include "Message.h"

Message::Message(string content, tm* savedTime, User* sender, User* receiver){
	this->content = content;
	this->sender = sender;
	this->receiver = receiver;
	this->currentTime.tm_gmtoff = savedTime->tm_gmtoff;
	this->currentTime.tm_hour = savedTime->tm_hour;
	this->currentTime.tm_isdst = savedTime->tm_isdst;
	this->currentTime.tm_mday = savedTime->tm_mday;
	this->currentTime.tm_min = savedTime->tm_min;
	this->currentTime.tm_mon = savedTime->tm_mon;
	this->currentTime.tm_sec = savedTime->tm_sec;
	this->currentTime.tm_hour = savedTime->tm_hour;
	this->currentTime.tm_wday = savedTime->tm_wday;
	this->currentTime.tm_yday = savedTime->tm_yday;
	this->currentTime.tm_mday = savedTime->tm_mday;
	this->currentTime.tm_year = savedTime->tm_year;
	this->currentTime.tm_zone = savedTime->tm_zone;
}

Message::Message(string content, User *sender, User *receiver) {
	this->content = content;
	this->sender = sender;
	this->receiver = receiver;
	// current date/time based on current system
	time_t tiempo = time(0);
	tm* estructura = localtime(&tiempo);
	this->currentTime.tm_gmtoff = estructura->tm_gmtoff;
	this->currentTime.tm_hour = estructura->tm_hour;
	this->currentTime.tm_isdst = estructura->tm_isdst;
	this->currentTime.tm_mday = estructura->tm_mday;
	this->currentTime.tm_min = estructura->tm_min;
	this->currentTime.tm_mon = estructura->tm_mon;
	this->currentTime.tm_sec = estructura->tm_sec;
	this->currentTime.tm_hour = estructura->tm_hour;
	this->currentTime.tm_wday = estructura->tm_wday;
	this->currentTime.tm_yday = estructura->tm_yday;
	this->currentTime.tm_mday = estructura->tm_mday;
	this->currentTime.tm_year = estructura->tm_year;
	this->currentTime.tm_zone = estructura->tm_zone;
}

Message::~Message() {
	delete this->currentTime;
}


User* Message::getSender() {
	return this->sender;
}

User* Message::getReceiver() {
	return this->receiver;
}

string Message::getContent() {
	return this->content;
}

tm* Message::getTime() {
	return &this->currentTime;
}


Json::Value Message::toJson() {
	Json::Value raiz;
	raiz["time"] = asctime(this->currentTime);
	raiz["content"] = this->getContent();
	return raiz;
}


