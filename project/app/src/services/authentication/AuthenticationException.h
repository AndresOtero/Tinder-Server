//
// Created by matias on 4/24/16.
//

#ifndef TINDER_SERVER_AUTHENTICATIONEXCEPTION_H
#define TINDER_SERVER_AUTHENTICATIONEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

class AuthenticationException: public runtime_error {
public:
	/**
	 * Constructor with message
	 * @param msg message of the error received.
	 */
	AuthenticationException(const string msg);
	virtual ~AuthenticationException();

};


#endif //TINDER_SERVER_AUTHENTICATIONEXCEPTION_H
