/*
 * ApiDispatcher.h
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#ifndef SRC_WEBSERVER_REQUESTDISPATCHER_H_
#define SRC_WEBSERVER_REQUESTDISPATCHER_H_


#include <string>
#include <functional>
#include "dispatcher/WebContext.h"
using namespace std;

class RequestDispatcher {

public:
	

	virtual void handle(RestRequest &, RestResponse &) = 0;
};

#endif /* SRC_WEBSERVER_REQUESTDISPATCHER_H_ */
