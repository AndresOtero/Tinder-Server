//
// Created by matias on 4/15/16.
//

#include <Logger.h>
#include "MatchDAO.h"

MatchDAO::MatchDAO(DBConnector *connector) {
	this->connector = connector;
}

MatchDAO::~MatchDAO() { }

bool MatchDAO::checkForLike(User* userA, User* userB) {
	string key = userA->getId();
	string value;
	if(!this->connector->getValueForKey(key, value)) return false;
	Json::Reader reader;
	Json::Value json;
	if(!reader.parse(value, json)) {
		LOG_ERROR << "DB data corrupted. Error parsing " << value <<" .";
		return false;
	}
	Json::Value likes = json["likes"];
	for (Json::ValueIterator itr = likes.begin(); itr != likes.end(); itr++) {
		if(itr->get("id", "ERROR").asString() == userB->getId())
			return true;
	}
	return false;
}

bool MatchDAO::checkForMatch(User* userA, User* userB) {
	string key = userA->getId();
	string value;
	if(!this->connector->getValueForKey(key, value)) return false;
	Json::Reader reader;
	Json::Value json;
	if(!reader.parse(value, json)) {
		LOG_ERROR << "DB data corrupted. Error parsing " << value <<" .";
		return false;
	}
	Json::Value matches = json["matches"];
	for (Json::ValueIterator itr = matches.begin(); itr != matches.end(); itr++) {
		if(itr->get("id", "ERROR").asString() == userB->getId())
			return true;
	}
	return false;
}


bool MatchDAO::saveLike(User* userA, User* userB) {
	string key = userA->getId();
	string value;
	bool isInDB = this->connector->getValueForKey(key,value);
	Json::Value json;
	if(!isInDB) {
		json["numLikes"] = 0;
		json["numMatches"] = 0;
		json["likes"] = Json::Value(Json::arrayValue);
		json["matches"] = Json::Value(Json::arrayValue);
	} else {
		Json::Reader reader;
		bool parseResult = reader.parse(value, json);
		//Do not add twice the like.
		if(this->checkForLike(userA, userB)) return true;
		if (!parseResult) {
			LOG_ERROR << "DB data corrupted. Error parsing " << value <<" .";
			return false;
		}
	}
	Json::Value newLike;
	//newLike["username"] = userB->getExternalId();
	newLike["id"] = userB->getId();
	json["numLikes"] = json["numLikes"].asInt() + 1;
	json["likes"].append(newLike);
	Json::FastWriter writer;
	string toSave = writer.write(json);
	this->connector->putValueInKey(key, toSave);
	if(this->checkForLike(userB, userA)) this->addMatch(userA, userB);
	return true;
}

void MatchDAO::addMatch(User* userA, User* userB) {
	string keyA = userA->getId();
	string keyB = userB->getId();
	string valueA;
	string valueB;
	this->connector->getValueForKey(keyA, valueA);
	this->connector->getValueForKey(keyB, valueB);
	Json::Value jsonA;
	Json::Value jsonB;
	Json::Reader reader;
	reader.parse(valueA, jsonA);
	reader.parse(valueB, jsonB);
	Json::Value matchA;
	Json::Value matchB;
	matchA["id"] = userB->getId();
	//matchA["externalid"] = userB->getId();
	//matchB["username"] = userA->getExternalId();
	matchB["id"] = userA->getId();
	jsonA["numMatches"] = jsonA["numMatches"].asInt() + 1;
	jsonA["matches"].append(matchA);
	jsonB["numMatches"] = jsonB["numMatches"].asInt() + 1;
	jsonB["matches"].append(matchB);
	Json::FastWriter writer;
	this->connector->putValueInKey(keyA, writer.write(jsonA));
	this->connector->putValueInKey(keyB, writer.write(jsonB));
}

int MatchDAO::getNumberOfLikes(User* user) {
	string value;
	string key = user->getId();
	bool resultado = this->connector->getValueForKey(key, value);
	if(!resultado) return 0;
	Json::Reader reader;
	Json::Value json;
	resultado = reader.parse(value, json);
	if(!resultado) {
		LOG_ERROR << "Data in the db corrupted. Can not parse " << value << " Check db.";
		return 0;
	}
	return json.get("numLikes", 0).asInt();
}

int MatchDAO::getNumberOfMatches(User* user) {
	string value;
	string key =  user->getId();
	bool resultado = this->connector->getValueForKey(key, value);
	if(!resultado) return 0;
	Json::Reader reader;
	Json::Value json;
	resultado = reader.parse(value, json);
	if(!resultado) {
		LOG_ERROR << "Data in the db corrupted. Can not parse " << value << " Check db.";
		return 0;
	}
	return json.get("numMatches", 0).asInt();
}

Json::Value MatchDAO::getMatches(User* user) {
	string key = user->getId();
	string value;
	bool isInDB = this->connector->getValueForKey(key,value);
	if(!isInDB) return Json::Value(Json::arrayValue);
	Json::Reader reader;
	Json::Value json;
	bool parseResult = reader.parse(value, json);
	if (!parseResult) {
		LOG_ERROR << "Data in the db corrupted. Can not parse " << value << " Check db.";
		return Json::Value(Json::arrayValue);
	}
	return json["matches"];
}





