//
// Created by jonathan on 25/05/16.
//

#ifndef TINDER_SERVER_USERVALIDATOR_H
#define TINDER_SERVER_USERVALIDATOR_H

#include <string>
using namespace std;
class UserValidator {

public:
    virtual bool isValid(string userid) = 0;
};


#endif //TINDER_SERVER_USERVALIDATOR_H
