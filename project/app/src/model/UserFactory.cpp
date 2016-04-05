#include "UserFactory.h"
#include "json/json/json.h"
#include "log/Logger.h"
#include "Location.h"

User* UserFactory::getUserByID(int id, SharedConnector connector){
	Json::Value root;
	if (!connector.getUserByID(id, root)) {
		LOG_ERROR << "Error obteniendo user con id " << id;
		return NULL;
	}

	unordered_map<string, set<string>> interests;
	Location location(0.0, 0.0);
	string userid = root[0].get("id", "ERROR").asString();
	string name = root[0].get("name", "ERROR").asString();
	string alias = root[0].get("alias", "ERROR").asString();
	string email = root[0].get("email", "ERROR").asString();
	string photo = root[0].get("photo_profile", "ERROR").asString();
	User* newUser = new User(userid, name, alias, email, photo, interests, location);
	return newUser;
}

list<User *> UserFactory::getAllUsers(SharedConnector connector) {
	list<User *> users;
	Json::Value root;
	if (!connector.getAllUsers(root)) {
		LOG_ERROR << "Error obteniendo la lista de users";
		return users;
	}

	for( Json::ValueIterator itr = root.begin() ; itr != root.end() ; itr++ ) {
		unordered_map<string, set<string>> interests;
		Location location(0.0, 0.0);
		string userid = itr->get("id", "ERROR").asString();
		string name = itr->get("name", "ERROR").asString();
		string alias = itr->get("alias", "ERROR").asString();
		string email = itr->get("email", "ERROR").asString();
		string photo = itr->get("photo_profile", "ERROR").asString();
		User* newUser = new User(userid, name, alias, email, photo, interests, location);
		users.push_back(newUser);
	}

	return users;
}
