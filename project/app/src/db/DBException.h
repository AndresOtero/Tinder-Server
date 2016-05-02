//
// Created by jonathan on 01/05/16.
//

#ifndef TINDER_SERVER_DBEXCEPTION_H
#define TINDER_SERVER_DBEXCEPTION_H
#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

class DBException: public runtime_error {

public:

    /**
     * Constructor with error
     * @param error error ocurred
     */
    DBException(string error);

    virtual ~DBException() { }
};


#endif //TINDER_SERVER_DBEXCEPTION_H
