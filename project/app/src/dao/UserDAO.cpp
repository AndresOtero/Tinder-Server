//
// Created by matias on 4/24/16.
//

#include <json/json.h>
#include <Logger.h>
#include <AuthenticationException.h>
#include "UserDAO.h"


UserDAO::UserDAO(SharedConnector* shared, DBConnector* db) {
	this->sharedConnector = shared;
	this->dbConnector = db;
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
		Json::Value user = itr->get("user", "ERROR");
		Json::FastWriter writer;
		Json::Value interestsJson = user.get("interests", "ERROR");
		unordered_map<string, set<string>> interests = this->populateInterests(interestsJson);
		string userid = user.get("id", "ERROR").asString();
		string name = user.get("name", "ERROR").asString();
		string alias = user.get("alias", "ERROR").asString();
		string email = user.get("email", "ERROR").asString();
		string photo = user.get("photo_profile", "ERROR").asString();
		string sex = user.get("sex", "ERROR").asString();
		int age = user.get("age", "ERROR").asInt();
		Location location(
				user.get("location", "ERROR").get("latitude", "ERROR").asDouble(),
				user.get("location", "ERROR").get("longitude", "ERROR").asDouble());
		User* newUser = new User(userid, name, alias, email, sex, age, photo, interests,
		                         location);
		users.push_back(newUser);
	}
	return users;
}

unordered_map<string, set<string>> UserDAO::populateInterests(Json::Value &root) {
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
	Json::Value userJson = this->assembleJsonFromUser(user);
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
	Json::Value userJson = this->assembleJsonFromUser(user);
	Json::Value root;
	root["user"] = userJson;
	Json::FastWriter writer;
	string data = writer.write(root);
	Json::Value response;
	if (!this->sharedConnector->postDataToURL(url, data, response)) {
		LOG_ERROR << "Error haciendo post del user nuevo";
		return false;
	}
	string id = response["user"]["id"].asString();
	user->setId(id);
	return true;
}

Json::Value UserDAO::assembleJsonFromUser(User* user) {
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
	userData["age"] = user->getAge();
	userData["sex"] = user->getSex();
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

//TODO esto deberia devolver una lista de objetos Interests
unordered_map<string, set<string>> UserDAO::getInterests() {
	string url = "/interests/";
	Json::Value root;
	if (!this->sharedConnector->getJsonFromURL(url, root) ) {
		LOG_ERROR << "Error obteniendo la lista de intereses";
		unordered_map<string, set<string>> mapa;
		return mapa;
	}
	unordered_map<string, set<string>> mapa = this->populateInterests(root["interests"]);
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


bool UserDAO::validateUsernamePassword(std::string username, std::string password) {
	std::string value;
	if (!this->dbConnector->getValueForKey(username, value)) return false;
	return !(value != password);
}


bool UserDAO::isUsernameTaken(std::string username) {
	std::string value;
	return (this->dbConnector->getValueForKey(username, value));
}

bool UserDAO::changePasswordForUser(std::string username, std::string currentPassword,std::string newPassword){
	if (!this->validateUsernamePassword(username, currentPassword)) {
		throw AuthenticationException("Combination of username and password invalid.");
	}
	return (this->dbConnector->putValueInKey(username, newPassword));
}

bool UserDAO::saveNewUsername(std::string username, std::string password) {
	if (this->isUsernameTaken(username)) {
		throw AuthenticationException("Username " + username + " already exists.");
	}
	return this->dbConnector->putValueInKey(username, password);
}


