//
// Created by matias on 4/24/16.
//

#include <json/json.h>
#include <Logger.h>
#include "UserDAO.h"


//TODO mensajes en ingles.
UserDAO::UserDAO(SharedConnector *shared) {
    this->sharedConnector = shared;
}

UserDAO::~UserDAO() { }

User *UserDAO::getUserById(int id) {
	Json::Value array;
	Json::Value root;
	std::string url = "/users/" + std::to_string(id);
	if (!this->sharedConnector->getJsonFromURL(url, root)) {
		LOG_ERROR << "Error obteniendo user con id " << id;
		return NULL;
	}
	array.append(root);
	return this->assembleUsersFromJson(array).front();
}

list<User *> UserDAO::getAllUsers() {
	Json::Value root;
	string url = "/users";
	if (!this->sharedConnector->getJsonFromURL(url, root) ) {
		LOG_ERROR << "Error obteniendo la lista de users";
		std::list<User *> users;
		return users;
	}
	Json::Value users = root.get("users","ERROR");
	return this->assembleUsersFromJson(users);
}

list<User *> UserDAO::assembleUsersFromJson(Json::Value &root) {
	std::list<User *> users;
	for (Json::ValueIterator itr = root.begin(); itr != root.end(); itr++) {
		Json::Value val = itr->get("user", "ERROR");
		users.push_back(User::fromExternalJson(val));
	}
	return users;
}


bool UserDAO::deleteUserByID(int id) {
	string url = "/users/" + to_string(id);
	if (!this->sharedConnector->deleteToURL(url)) {
		LOG_ERROR << "Error deleting user con ID: " << to_string(id);
		return false;
	}
	return true;
}

bool UserDAO::updateUserProfile(User* user) {
	string url = "/users/" + user->getId();
	Json::Value userJson;
	user->toExternalJson(userJson);
	Json::Value root;
	Json::Value version;
	version["version"] = "0.1";
	root["user"] = userJson;
	root["metadata"] = version;
	Json::FastWriter writer;
	string data = writer.write(root);
	Json::Value response;
	if (!this->sharedConnector->postDataToURL(url, data, response)) {
		LOG_ERROR << "Error haciendo put para el user con id=" << user->getId();
		return false;
	}
	return true;
}

bool UserDAO::saveNewUser(User* user) {
	string url = "/users/";
	Json::Value userJson;
	user->toExternalJson(userJson);
	Json::Value root;
	root["user"] = userJson;
	Json::FastWriter writer;
	string data = writer.write(root);
	Json::Value response;
	if (!this->sharedConnector->postDataToURL(url, data, response)) {
		LOG_ERROR << "Error haciendo post del user nuevo";
		return false;
	}
	int id = response["user"]["id"].asInt();
	user->setExternalId(id);
	return true;
}


//TODO esto deberia devolver una lista de objetos Interests
unordered_map<string, set<string>> UserDAO::getInterests() {
	string url = "/interests/";
	Json::Value root;
	if (!this->sharedConnector->getJsonFromURL(url, root) ) {
		LOG_ERROR << "Error obteniendo la lista de intereses";
		unordered_map<string, set<string>> mapa;
		return mapa;
	}
	unordered_map<string, set<string>> mapa = User::populateInterests(root["interests"]);
	return mapa;
}

bool UserDAO::saveNewInterest(string category, string value) {
	string url = "/interests/";
	string response;
	Json::Value root;
	Json::Value interest;
	interest["category"] = category;
	interest["value"] = value;
	root["interest"] = interest;
	Json::FastWriter writer;
	string data = writer.write(root);
	if (!this->sharedConnector->postDataToURL(url, data, response)) {
		LOG_ERROR << "Error haciendo post del interest nuevo";
		return false;
	}
	return true;
}



