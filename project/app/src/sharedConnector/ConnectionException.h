//
// Created by jonathan on 04/05/16.
//

#ifndef TINDER_SERVER_CONNECTIONEXCEPTION_H
#define TINDER_SERVER_CONNECTIONEXCEPTION_H
#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

class ConnectionException: public runtime_error {
public:
    ConnectionException (string error);
    bool isBadRequest();
};


#endif //TINDER_SERVER_CONNECTIONEXCEPTION_H
