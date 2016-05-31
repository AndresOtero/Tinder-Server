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
	Candidate(User* user, double limit);
	virtual ~Candidate();
	User* getUser();

	bool operator < (const Candidate &other);
	bool operator > (const Candidate &other);

	int score;
	int numLiked;
	double distanceToUser;
	double distanceLimit;

private:
	User* user;
};


#endif //TINDER_SERVER_CANDIDATE_H
