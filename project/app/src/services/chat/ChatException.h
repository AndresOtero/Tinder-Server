//
// Created by matias on 4/24/16.
//

#ifndef TINDER_SERVER_CHATEXCEPTION_H
#define TINDER_SERVER_CHATEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

class ChatException: public runtime_error {
public:
	/**
	 * Constructor with message
	 * @param msg message of the error received.
	 */
	ChatException(const string msg);
	virtual ~ChatException();

};


#endif //TINDER_SERVER_AUTHENTICATIONEXCEPTION_H
