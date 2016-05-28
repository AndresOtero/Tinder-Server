//
// Created by matias on 4/24/16.
//

#include <json/json.h>
#include <Logger.h>
#include <ConnectionException.h>
#include "UserDAO.h"
#include "UserNotFoundException.h"


//TODO mensajes en ingles.
UserDAO::UserDAO(SharedConnector *shared) {
    this->sharedConnector = shared;
}

UserDAO::~UserDAO() { }

User *UserDAO::getUserById(int id) {
	Json::Value array;
	Json::Value root;
	std::string url = "/users/" + std::to_string(id);
    try {
        this->sharedConnector->getJsonFromURL(url, root);
        array.append(root);
        return this->assembleUsersFromJson(array).front();
    } catch (ConnectionException &e) {
        if(e.isBadRequest()) {
            throw UserNotFoundException(to_string(id));
        }
        throw e;
    }
}

list<User *> UserDAO::getAllUsers() {
	Json::Value root;
	string url = "/users";
	this->sharedConnector->getJsonFromURL(url, root);
		//LOG_ERROR << "Error obteniendo la lista de users";
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


void UserDAO::deleteUserByID(int id) {
	string url = "/users/" + to_string(id);
	this->sharedConnector->deleteToURL(url);
}

void UserDAO::updateUser(User *user) {
	string url = "/users/" + to_string(user->getExternalId());
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
	this->sharedConnector->putDataToURL(url, data, response);
}

void UserDAO::saveNewUser(User *user) {
	string url = "/users";
	Json::Value userJson;
	user->toExternalJson(userJson);
	Json::Value root;
    userJson["id"] = "";
    root["user"] = userJson;
	Json::FastWriter writer;
	string data = writer.write(root);
	Json::Value response;
	this->sharedConnector->postDataToURL(url, data, response);
	int id = response["user"]["id"].asInt();
	user->setExternalId(id);
}


//TODO esto deberia devolver una lista de objetos Interests
unordered_map<string, set<string>> UserDAO::getInterests() {
	string url = "/interests/";
	Json::Value root;
	this->sharedConnector->getJsonFromURL(url, root);
	unordered_map<string, set<string>> mapa = User::populateInterests(root["interests"]);
	return mapa;
}



