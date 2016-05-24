//
// Created by matias on 5/19/16.
//

#ifndef TINDER_SERVER_CORRUPTOPTIONSEXCEPTION_H
#define TINDER_SERVER_CORRUPTOPTIONSEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

class CorruptOptionsException : public runtime_error{
public:
	/**
	 * Constructor with message
	 * @param msg message of the error received.
	 */
	CorruptOptionsException(const string msg);
	virtual ~CorruptOptionsException();

};


#endif //TINDER_SERVER_CORRUPTOPTIONSEXCEPTION_H
