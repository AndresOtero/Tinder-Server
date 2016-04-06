/*
 * PathVariableException.cpp
 *
 *  Created on: 6 de abr. de 2016
 *      Author: jonathan
 */

#include <PathVariableException.h>

PathVariableException::PathVariableException(string uri): runtime_error(uri) {
	// TODO Auto-generated constructor stub

}

PathVariableException::~PathVariableException() {
	// TODO Auto-generated destructor stub
}

