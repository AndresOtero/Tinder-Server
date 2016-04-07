#include "UserFactory.h"
#include "json/json/json.h"
#include "log/Logger.h"
#include "Location.h"
#include "sharedConnector/SharedConnector.h"

UserFactory::UserFactory(SharedConnector* connector) {
	this->connector = connector;
}

UserFactory::~UserFactory() {}

list<User *> UserFactory::assembleUsersFromJson(Json::Value &root) {
	list<User *> users;
	for( Json::ValueIterator itr = root.begin() ; itr != root.end() ; itr++ ) {
	unordered_map<string, set<string>> interests;
	Json::Value user = itr->get("user","ERROR");
	string userid = user.get("id", "ERROR").asString();
	string name = user.get("name", "ERROR").asString();
	string alias = user.get("alias", "ERROR").asString();
	string email = user.get("email", "ERROR").asString();
	string photo = user.get("photo_profile", "ERROR").asString();
	Location location(user.get("location", "ERROR").get("latitude", "ERROR").asDouble(), 
		user.get("location", "ERROR").get("longitude", "ERROR").asDouble());
	User* newUser = new User(userid, name, alias, email, photo, interests, location);
	users.push_back(newUser);
	}
	return users;
}

User* UserFactory::getUserByID(int id){
	Json::Value array;
	Json::Value root;
	std::string url = "/users/" + std::to_string(id);
	if (!this->connector->getJsonFromURL(url, root)) {
		LOG_ERROR << "Error obteniendo user con id " << id;
		return NULL;
	}
	array.append(root);
	return this->assembleUsersFromJson(array).front();
}


list<User *> UserFactory::getAllUsers() {
	Json::Value root;
	string url = "/users";
	if (!this->connector->getJsonFromURL(url, root) ) {
		LOG_ERROR << "Error obteniendo la lista de users";
		list<User *> users;
		return users;
	}
	Json::Value users = root.get("users","ERROR");
	return this->assembleUsersFromJson(users);
}
