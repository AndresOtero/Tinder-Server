//
// Created by matias on 4/25/16.
//

#include "UserNotFoundException.h"

UserNotFoundException::UserNotFoundException(string msg) :
		runtime_error("User with id: " + msg + " not found.") { }


UserNotFoundException::~UserNotFoundException() { }

