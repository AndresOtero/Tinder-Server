#include "Location.h"

Location::Location(double lat, double lon) {
	this->latitude = lat;
	this->longitude = lon;
}

Location::Location() {
	this->latitude = 0;
	this->longitude = 0;
}

Location::~Location() {}

double Location::getLatitude() {
	return this->latitude;
}

double Location::getLongitude() {
	return this->longitude;
}

void Location::setLatitude(double latitude) {
	this->latitude = latitude;
}

void Location::setLongitude(double longitude) {
	this->longitude = longitude;
}
