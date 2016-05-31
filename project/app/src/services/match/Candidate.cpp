//
// Created by matias on 5/6/16.
//

#include "Candidate.h"

Candidate::Candidate(User *user, double limit) {
	this->user = user;
	this->score = 0;
	this->numLiked = 0;
	this->distanceToUser = 0;
	this->distanceLimit = limit;
}

Candidate::Candidate(User *user) {
	this->user = user;
	this->score = 0;
	this->numLiked = 0;
	this->distanceToUser = 0;
	this->distanceLimit = 400;
}

Candidate::~Candidate() { }

User *Candidate::getUser() {
	return this->user;
}


bool Candidate::operator<(const Candidate &other) {
	return this->score < other.score;
}

bool Candidate::operator>(const Candidate &other) {
	return this->score > other.score;
}



