/*
 * NoSuchMethodHandlerException.cpp
 *
 *  Created on: 5 de abr. de 2016
 *      Author: jonathan
 */

#include <NoSuchMethodHandlerException.h>

NoSuchMethodHandlerException::NoSuchMethodHandlerException(string uri): runtime_error("Handler for " + uri + " not found") {
	// TODO Auto-generated constructor stub

}

NoSuchMethodHandlerException::~NoSuchMethodHandlerException() {
	// TODO Auto-generated destructor stub
}

