//
// Created by matias on 4/15/16.
//

#include <Logger.h>
#include <DBException.h>
#include <iomanip>
#include "MatchDAO.h"
#include "DBException.h"

MatchDAO::MatchDAO(DBConnector *connector) {
	this->connector = connector;
}

MatchDAO::~MatchDAO() { }


Json::Value MatchDAO::getUserEntry(User *user) {
	string key = user->getId();
	bool isInDB = this->connector->exist(key);
	if(!isInDB) this->initializeUserEntry(user);
	string value = this->connector->getValueForKey(key);
	Json::Reader reader;
	Json::Value json;
	if(!reader.parse(value, json)) throw DBException("Error parsing DB. Data may be corrupted");
	return json;
}


bool MatchDAO::checkForLike(User* userA, User* userB) {
	Json::Value json = this->getUserEntry(userA);
	Json::Value likes = json["likes"];
	for (Json::ValueIterator itr = likes.begin(); itr != likes.end(); itr++) {
		if(itr->get("id", "ERROR").asString() == userB->getId())
			return true;
	}
	return false;
}

bool MatchDAO::checkForMatch(User* userA, User* userB) {
	Json::Value json = this->getUserEntry(userA);
	Json::Value matches = json["matches"];
	for (Json::ValueIterator itr = matches.begin(); itr != matches.end(); itr++) {
		if(itr->get("id", "ERROR").asString() == userB->getId())
			return true;
	}
	return false;
}

tm* MatchDAO::getLastRequestTime(User *user) {
	Json::Value json = this->getUserEntry(user);
	string fecha = json["lastRequest"].asString();
	tm* lastDateStruct = (tm*) malloc(sizeof(tm));
	if(!strptime(fecha.c_str(),"%a %b %e %H:%M:%S %Y" ,lastDateStruct)) throw DBException("ERROR parsing last requested time.");
	return lastDateStruct;
}


void MatchDAO::initializeUserEntry(User *user) {
	Json::Value json;
	time_t currentDay = time(NULL);
	struct tm* timeStruct = localtime(&currentDay);
	if (timeStruct->tm_mday - 1 == 0)  timeStruct->tm_mday = 30;
	else timeStruct->tm_mday = timeStruct->tm_mday - 1;

	string timeStamp(asctime(timeStruct));
	json["lastRequest"] = timeStamp;
	json["numLiked"] = 0;
	json["numLikes"] = 0;
	json["numMatches"] = 0;
	json["likes"] = Json::Value(Json::arrayValue);
	json["matches"] = Json::Value(Json::arrayValue);
	Json::FastWriter writer;
	this->connector->putValueInKey(user->getId(), writer.write(json));
}


int MatchDAO::getNumLiked(User *user) {
	Json::Value json = this->getUserEntry(user);
	return json["numLiked"].asInt();
}


void MatchDAO::saveLike(User *userA, User *userB) {
	Json::Value json = this->getUserEntry(userA);
	Json::Value newLike;
	newLike["id"] = userB->getId();
	json["numLikes"] = json["numLikes"].asInt() + 1;
	json["likes"].append(newLike);
	Json::FastWriter writer;
	string toSave = writer.write(json);
	this->connector->putValueInKey(userA->getId(), toSave);
	Json::Value jsonB = this->getUserEntry(userB);
	jsonB["numLiked"] = jsonB["numLiked"].asInt() + 1;
	this->connector->putValueInKey(userB->getId(), writer.write(jsonB));
}

void MatchDAO::addMatch(User* userA, User* userB) {
	Json::Value jsonA = this->getUserEntry(userA);
	Json::Value jsonB = this->getUserEntry(userB);
	Json::Value matchA;
	Json::Value matchB;
	matchA["id"] = userB->getId();
	matchB["id"] = userA->getId();
	jsonA["numMatches"] = jsonA["numMatches"].asInt() + 1;
	jsonA["matches"].append(matchA);
	jsonB["numMatches"] = jsonB["numMatches"].asInt() + 1;
	jsonB["matches"].append(matchB);
	Json::FastWriter writer;
	this->connector->putValueInKey(userA->getId(), writer.write(jsonA));
	this->connector->putValueInKey(userB->getId(), writer.write(jsonB));
}

int MatchDAO::getNumberOfLikes(User* user) {
	Json::Value json = this->getUserEntry(user);
	int likes= json.get("numLikes", 0).asInt();
	return likes;
}

int MatchDAO::getNumberOfMatches(User* user) {
	Json::Value json = this->getUserEntry(user);
	return json.get("numMatches", 0).asInt();
}

list<string> MatchDAO::getMatches(User* user) {
	Json::Value json = this->getUserEntry(user);
	list<string> lista;
	for (Json::ValueIterator itr = json["matches"].begin(); itr != json["matches"].end(); itr++) {
		lista.push_front(itr->get("id", "ERROR").asString());
	}
	return lista;
}


list <string> MatchDAO::getLikes(User *user) {
	Json::Value json = this->getUserEntry(user);
	list<string> lista;
	for (Json::ValueIterator itr = json["likes"].begin(); itr != json["likes"].end(); itr++) {
		lista.push_front(itr->get("id", "ERROR").asString());
	}
	return lista;
}







