#include "User.h"

//Crear usando el userFactory!!
User::User(string id, string name, int externalId, string email, string sex, int age, string photoURL,
		   unordered_map<string, set<string>> interests, Location location){
	this->id = id;
	this->name = name;
	this->externalId = externalId;
	this->email = email;
	this->photoURL = photoURL;
	this->interests = interests;
	this->location = location;
	this->sex = sex;
	this->age = age;
}

User::~User() {}

string User::getId() {
	return this->id;
}

string User::getName() {
	return	this->name;
}

int User::getExternalId() {
	return this->externalId;
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

void User::setExternalId(int alias) {
	this->externalId = alias;
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

list<Interest*> User::getInterests() {
	std::list<Interest*> lista;
	for(auto it = this->interests.begin(); it != this->interests.end(); ++it) {
		for(auto setit = it->second.begin(); setit != it->second.end(); ++setit) {
			lista.push_front(new Interest(it->first, *setit));
		}
	}
	return lista;
}

void User::setId(string id) {
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
	userData["id"] = this->getId();
	userData["externalId"] = this->getExternalId();

	userData = bodyToJson(userData, *this);
	return userData;
}

Json::Value &User::bodyToJson(Json::Value &userData, User &user) {
	Json::Value interests;
	Json::Value location;
	location["latitude"] = user.getLatitude();
	location["longitude"] = user.getLongitude();
	userData["name"] = user.getName();
	userData["email"] = user.getEmail();
	userData["photo_profile"] = user.getPhotoURL();
	userData["alias"] = user.getAlias();
	userData["age"] = user.getAge();
	userData["sex"] = user.getSex();
	userData["location"] = location;
	for (auto it = user.interests.begin(); it != user.interests.end(); ++it ) {
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
	Json::Value interestsJson = user.get("interests", "");
	this->interests = this->populateInterests(interestsJson);
	this->externalId = user.get("externalId", 0).asInt();
	this->id = user.get("email", "").asString();
	readCommonBody(user, *this);
}

void User::readCommonBody(const Json::Value &values, User &user) {
	user.setAlias(values.get("alias", "").asString());
	user.setName(values.get("name", "").asString());
	user.setEmail(values.get("email", "").asString());
	user.setPhotoURL(values.get("photo_profile", "").asString());
	user.setSex(values.get("sex", "").asString());
	user.setAge(values.get("age", "").asInt());
	user.setLatitude(values.get("location", "").get("latitude", "").asDouble());
	user.setLongitude(values.get("location", "").get("longitude", "").asDouble());
}

unordered_map<string, set<string>> User::populateInterests(Json::Value &root) {
	unordered_map<string, set<string>> mapa;
	for (Json::ValueIterator itr = root.begin(); itr != root.end(); itr++) {
		string category = itr->get("category", "").asString();
		string value = itr->get("value", "").asString();
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

void User::toExternalJson(Json::Value &userData) {
	Json::Value interests;
	userData["id"] = this->getExternalId();
	userData = bodyToJson(userData, *this);
	for (auto it = this->interests.begin(); it != this->interests.end(); ++it ) {
		for (set<string>::iterator setit = it->second.begin(); setit != it->second.end(); ++setit) {
			Json::Value valor;
			valor["category"] = it->first;
			valor["value"] = *setit;
			interests.append(valor);
		}
	}
	userData["interests"] = interests;
}

User *User::fromExternalJson(Json::Value &value) {
	User * user = new User();
	Json::FastWriter writer;
	Json::Value interestsJson = value.get("interests", "");
	unordered_map<string, set<string>> interests = populateInterests(interestsJson);
	user->setExternalId(value.get("id", -1).asInt());
	user->setId(value.get("email", "").asString());
	User::readCommonBody(value, *user);
	return user;
}


User::User() {


}

void User::setAlias(string alias) {
	this->alias = alias;
}

string User::getAlias() {
	return this->alias;
}




