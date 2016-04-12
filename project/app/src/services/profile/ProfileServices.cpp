#include <iostream>
#include "ProfileServices.h"
#include "../../log/Logger.h"

ProfileServices::ProfileServices(SharedConnector* connector) {
	this->connector = connector;
}

ProfileServices::~ProfileServices() {}

unordered_map<string, set<string>> ProfileServices::populateInterests(Json::Value &root) {
	unordered_map<string, set<string>> mapa;
	for (Json::ValueIterator itr = root.begin(); itr != root.end(); itr++) {
		string category = itr->get("category", "ERROR").asString();
		string value = itr->get("value", "ERROR").asString();
		unordered_map<std::string, set<string>>::const_iterator got = mapa.find(category);
		if (got == mapa.end()) {
			//todavia no esta esa categoria en el map
			set<string> newSet;
			newSet.insert(value);
			mapa[category] = newSet;
		} else {
			set<string> valores = got->second;
			valores.insert(value);
			mapa[category] = valores;
		}
	}
	return mapa;
}

list<User *> ProfileServices::assembleUsersFromJson(Json::Value &root) {
	list<User *> users;
	for (Json::ValueIterator itr = root.begin(); itr != root.end(); itr++) {
		Json::Value user = itr->get("user", "ERROR");
		Json::FastWriter writer;
		//cout << writer.write(user);
		Json::Value interestsJson = user.get("interests", "ERROR");
		unordered_map<string, set<string>> interests = this->populateInterests(interestsJson);
		string userid = user.get("id", "ERROR").asString();
		string name = user.get("name", "ERROR").asString();
		string alias = user.get("alias", "ERROR").asString();
		string email = user.get("email", "ERROR").asString();
		string photo = user.get("photo_profile", "ERROR").asString();
		Location location(
				user.get("location", "ERROR").get("latitude", "ERROR").asDouble(),
				user.get("location", "ERROR").get("longitude", "ERROR").asDouble());
		User* newUser = new User(userid, name, alias, email, photo, interests,
				location);
		users.push_back(newUser);
	}
	return users;
}

User* ProfileServices::getUserByID(int id){
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


list<User *> ProfileServices::getAllUsers() {
	Json::Value root;
	string url = "/users";
	if (!this->connector->getJsonFromURL(url, root) ) {
		LOG_ERROR << "Error obteniendo la lista de users";
		std::list<User *> users;
		return users;
	}
	Json::Value users = root.get("users","ERROR");
	return this->assembleUsersFromJson(users);
}


bool ProfileServices::deleteUserByID(int id) {
	string url = "/users/" + to_string(id);
	if (!this->connector->deleteToURL(url)) {
		LOG_ERROR << "Error deleting user con ID: " << to_string(id);
		return false;
	}
	return true;
}

bool ProfileServices::updateUserProfile(User* user) {
	string url = "/users/" + user->getId();
	Json::Value userJson = this->assembleJsonFromUser(user);
	Json::Value root;
	Json::Value version;
	version["version"] = "0.1";
	root["user"] = userJson;
	root["metadata"] = version;
	Json::FastWriter writer;
	string data = writer.write(root);
	cout << data;
	Json::Value response;
	if (!this->connector->putDataToURL(url, data, response)) {
		LOG_ERROR << "Error haciendo put para el user con id=" << user->getId();
		return false;
	}
	return true;
}

bool ProfileServices::saveNewUser(User* user) {
	string url = "/users/";
	Json::Value userJson = this->assembleJsonFromUser(user);
	Json::Value root;
	root["user"] = userJson;
	Json::FastWriter writer;
	string data = writer.write(root);
	Json::Value response;
	if (!this->connector->postDataToURL(url, data, response)) {
				LOG_ERROR << "Error haciendo post del user nuevo";
		return false;
	}
	string id = response["user"]["id"].asString();
	user->setId(id);
	return true;
}

Json::Value ProfileServices::assembleJsonFromUser(User* user) {
	Json::Value userData;
	Json::Value location;
	Json::Value interests;
	location["latitude"] = user->getLatitude();
	location["longitude"] = user->getLongitude();
	userData["id"] = user->getId();
	userData["name"] = user->getName();
	userData["alias"] = user->getAlias();
	userData["email"] = user->getEmail();
	userData["photo_profile"] = user->getPhotoURL();
	userData["location"] = location;
	unordered_map<string, set<string>> intereses = user->getInterests();
	for ( auto it = intereses.begin(); it != intereses.end(); ++it ) {
		for (set<string>::iterator setit = it->second.begin(); setit != it->second.end(); ++setit) {
			Json::Value valor;
			valor["category"] = it->first;
			valor["value"] = *setit;
			interests.append(valor);
		}
	}
	userData["interests"] = interests;
	return userData;
}