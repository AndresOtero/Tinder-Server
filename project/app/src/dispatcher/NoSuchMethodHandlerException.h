/*
 * NoSuchMethodHandlerException.h
 *
 *  Created on: 5 de abr. de 2016
 *      Author: jonathan
 */

#ifndef APP_SRC_DISPATCHER_NOSUCHMETHODHANDLEREXCEPTION_H_
#define APP_SRC_DISPATCHER_NOSUCHMETHODHANDLEREXCEPTION_H_

#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

class NoSuchMethodHandlerException: public runtime_error {
public:

	NoSuchMethodHandlerException(string uri);
	virtual ~NoSuchMethodHandlerException();
};

#endif /* APP_SRC_DISPATCHER_NOSUCHMETHODHANDLEREXCEPTION_H_ */
