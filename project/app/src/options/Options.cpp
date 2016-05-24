//
// Created by matias on 5/19/16.
//

#include "Options.h"


Options::Options(string LogLevel, string SharedServerURL, string DbLocation) {
	this->LogLevel = LogLevel;
	this->SharedServerURL = SharedServerURL;
	this->DbLocation = DbLocation;
}

Options::~Options() { }

string Options::getLogLevel() {
	return this->LogLevel;
}

string Options::getSharedServerURL() {
	return this->SharedServerURL;
}

string Options::getDbLocation() {
	return this->DbLocation;
}

