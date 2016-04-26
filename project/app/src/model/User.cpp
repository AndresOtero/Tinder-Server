#include "User.h"

//Crear usando el userFactory!!
User::User(int id, string name, string alias,string email, string sex, int age, string photoURL,
	unordered_map<string, set<string>> interests, Location location){
	this->id = id;
	this->name = name;
	this->alias = alias;
	this->email = email;
	this->photoURL = photoURL;
	this->interests = interests;
	this->location = location;
	this->sex = sex;
	this->age = age;
}

User::~User() {}

int User::getId() {
	return this->id;
}

string User::getName() {
	return	this->name;
}

string User::getAlias() {
	return this->alias;
}

string User::getEmail() {
	return this->email;
}

string User::getPhotoURL() {
	return this->photoURL;
}

double User::getLatitude() {
	return this->location.getLatitude();
}

double User::getLongitude() {
	return this->location.getLongitude();
}

void User::setName(string name){
	this->name = name;
}

void User::setAlias(string alias) {
	this->alias = alias;
}

void User::setEmail(string email) {
	this->email = email;
}

void User::setPhotoURL(string url) {
	this->photoURL = url;
}

void User::setLatitude(double latitude) {
	this->location.setLatitude(latitude);
}

void User::setLongitude(double longitude) {
	this->location.setLongitude(longitude);
}

unordered_map<string, set<string>> User::getInterests() {
	return this->interests;
}

void User::setId(int id) {
	this->id = id;
}

void User::setSex(string sex) {
	this->sex = sex;
}

void User::setAge(int age) {
	this->age = age;
}

int User::getAge() {
	return this->age;
}

string User::getSex() {
	return this->sex;
}

Json::Value User::toJson() {
	Json::Value userData;
	Json::Value location;
	Json::Value interests;
	location["latitude"] = this->getLatitude();
	location["longitude"] = this->getLongitude();
	userData["id"] = this->getId();
	userData["name"] = this->getName();
	userData["alias"] = this->getAlias();
	userData["email"] = this->getEmail();
	userData["photo_profile"] = this->getPhotoURL();
	userData["age"] = this->getAge();
	userData["sex"] = this->getSex();
	userData["location"] = location;
	for ( auto it = this->interests.begin(); it != this->interests.end(); ++it ) {
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

User::User(Json::Value & user) {
	Json::FastWriter writer;
	Json::Value interestsJson = user.get("interests", "ERROR");
	unordered_map<string, set<string>> interests = this->populateInterests(interestsJson);
	this->id = user.get("id", "ERROR").asInt();
	this->name = user.get("name", "ERROR").asString();
	this->alias = user.get("alias", "ERROR").asString();
	this->email = user.get("email", "ERROR").asString();
	this->photoURL = user.get("photo_profile", "ERROR").asString();
	this->sex = user.get("sex", "ERROR").asString();
	this->age = user.get("age", "ERROR").asInt();
	this->location = Location(
			user.get("location", "ERROR").get("latitude", "ERROR").asDouble(),
			user.get("location", "ERROR").get("longitude", "ERROR").asDouble());

}

unordered_map<string, set<string>> User::populateInterests(Json::Value &root) {
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