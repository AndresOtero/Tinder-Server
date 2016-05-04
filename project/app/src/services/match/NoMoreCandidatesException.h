//
// Created by matias on 5/4/16.
//

#ifndef TINDER_SERVER_NOMORECANDIDATESEXCEPTION_H
#define TINDER_SERVER_NOMORECANDIDATESEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;
using std::runtime_error;

class NoMoreCandidatesException: public runtime_error {
public:
	/**
	 * Constructor with message
	 * @param msg message of the error received.
	 */
	NoMoreCandidatesException(const string msg);
	virtual ~NoMoreCandidatesException();
};


#endif //TINDER_SERVER_NOMORECANDIDATESEXCEPTION_H
