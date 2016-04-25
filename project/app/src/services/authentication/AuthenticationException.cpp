//
// Created by matias on 4/24/16.
//

#include "AuthenticationException.h"


AuthenticationException::AuthenticationException(const string msg) : runtime_error(msg) {

}

AuthenticationException::~AuthenticationException() {

}

