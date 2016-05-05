//
// Created by jonathan on 04/05/16.
//

#ifndef TINDER_SERVER_SERVICEEXCEPTION_H
#define TINDER_SERVER_SERVICEEXCEPTION_H


#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

class ServiceException: public runtime_error {
public:
    ServiceException(string id);
    virtual ~ServiceException();
};


#endif //TINDER_SERVER_SERVICEEXCEPTION_H
