//
// Created by matias on 4/25/16.
//

#include "UserNotFoundException.h"
#include <string>
using namespace std;
UserNotFoundException::UserNotFoundException(string id) :
		runtime_error("User with id: " + id + " not found.") { }


UserNotFoundException::~UserNotFoundException() { }

