/*
 * NoSuchMethodHandlerException.cpp
 *
 *  Created on: 5 de abr. de 2016
 *      Author: jonathan
 */

#include <PathVariableException.h>

PathVariableException::PathVariableException(string uri): runtime_error("Handler for " + uri + " not found") {
	// TODO Auto-generated constructor stub

}

PathVariableException::~PathVariableException() {
	// TODO Auto-generated destructor stub
}

