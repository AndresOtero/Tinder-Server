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

	/**
	 * Handle a request dispatching to the correct handler
	 * @param request RestRequest
	 * @param response RestResponse where tp build the response
	 */

	virtual void handle(RestRequest & request, RestResponse & response) = 0;
	virtual ~RequestDispatcher(){};
};

#endif /* SRC_WEBSERVER_REQUESTDISPATCHER_H_ */
