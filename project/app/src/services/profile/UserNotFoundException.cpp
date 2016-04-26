//
// Created by matias on 4/25/16.
//

#include "UserNotFoundException.h"
#include <string>
using namespace std;
UserNotFoundException::UserNotFoundException(int id) :
		runtime_error("User with id: " + to_string(id) + " not found.") { }


UserNotFoundException::~UserNotFoundException() { }

