//
// Created by matias on 5/6/16.
//

#ifndef TINDER_SERVER_CANDIDATE_H
#define TINDER_SERVER_CANDIDATE_H


#include <User.h>

/**
 * @class Candidate
 * Provides the necessary items to evaluate the candidates.
 */
class Candidate {
public:
	Candidate(User* user);
	virtual ~Candidate();
	User* getUser();

	bool operator < (const Candidate &other);
	bool operator > (const Candidate &other);

	int score;
	int numLiked;

private:
	User* user;
};


#endif //TINDER_SERVER_CANDIDATE_H
