//
// Created by jonathan on 04/05/16.
//

#include "ConnectionException.h"

ConnectionException::ConnectionException(string error): runtime_error(error) {

}

bool ConnectionException::isBadRequest() {
    string e = this->what();
    std::size_t found = e.find("Bad Request");
    return found!=std::string::npos;
}



