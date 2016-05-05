//
// Created by jonathan on 04/05/16.
//

#include "ServiceException.h"

ServiceException::ServiceException(string error): runtime_error(error) {

}

ServiceException::~ServiceException() {

}



