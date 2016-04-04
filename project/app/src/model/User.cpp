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