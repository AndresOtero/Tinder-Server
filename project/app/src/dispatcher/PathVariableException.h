/*
 * NoSuchMethodHandlerException.h
 *
 *  Created on: 5 de abr. de 2016
 *      Author: jonathan
 */

#ifndef APP_SRC_DISPATCHER_PATHVARIABLEEXCEPTION_H_
#define APP_SRC_DISPATCHER_PATHVARIABLEEXCEPTION_H_

#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

class PathVariableException: public runtime_error {
public:

	PathVariableException(string uri);
	virtual ~PathVariableException();
};

#endif /* APP_SRC_DISPATCHER_PATHVARIABLEEXCEPTION_H_ */
