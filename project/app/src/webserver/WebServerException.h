//
// Created by jonathan on 25/05/16.
//

#ifndef TINDER_SERVER_WEBSERVEREXCEPTION_H
#define TINDER_SERVER_WEBSERVEREXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

class WebServerException: public runtime_error {
public:
    /**
     * Constructor with message
     * @param msg message of the error received.
     */
    WebServerException(const string msg);
    virtual ~WebServerException();
};


#endif //TINDER_SERVER_WEBSERVEREXCEPTION_H
