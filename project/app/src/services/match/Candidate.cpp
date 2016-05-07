//
// Created by matias on 5/6/16.
//

#include "Candidate.h"


Candidate::Candidate(User *user) {
	this->user = user;
	this->score = 0;
	this->numLiked = 0;
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



