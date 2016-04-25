//
// Created by matias on 4/25/16.
//

#ifndef TINDER_SERVER_USERNOTFOUNDEXCEPTION_H
#define TINDER_SERVER_USERNOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

class UserNotFoundException: public runtime_error {
public:
	UserNotFoundException(string msg);
	virtual ~UserNotFoundException();
};


#endif //TINDER_SERVER_USERNOTFOUNDEXCEPTION_H
