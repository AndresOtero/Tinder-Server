#include "User.h"

//Crear usando el userFactory!!
User::User(string id, string name, string alias,string email, string photoURL, 
	unordered_map<string, set<string>> interests, Location location){
	this->id = id;
	this->name = name;
	this->alias = alias;
	this->email = email;
	this->photoURL = photoURL;
	this->interests = interests;
	this->location = location;
}

User::~User() {}

string User::getId() {
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

void User::setId(string id) {
	this->id = id;
}
