/*
 * ApiDispatcher.h
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#ifndef SRC_DISPATCHER_APIDISPATCHER_H_
#define SRC_DISPATCHER_APIDISPATCHER_H_
#include "webserver/RequestDispatcher.h"
#include "webserver/RestRequest.h"
#include <string>
#include <functional>
#include "WebContext.h"
#include "EndPoint.h"
#include <map>
using namespace std;


/**
 * @class ApiDispatcher
 * Provides RestRequests dispatching to their respective handlers
 *
 * @author jtierno
 *
 */

class ApiDispatcher: public RequestDispatcher {
private:
	/**
	 * Requests Handlers by HTTP Methods
	 */
	map<RestRequest::Method, EndPoint *> endpoints;

	/**
	 * Default Handler function from inexistent methods.
	 */
	function<void(WebContext&)> defFunction;
public:
	ApiDispatcher();
	virtual ~ApiDispatcher();
	/**
	 * Register a handler for a uri and http method
	 * @see RestRequest::Method
	 * @param method Http Method to handle
	 * @param uri Uri patern to handle, uri parameters need to be enclosing by ## (ex: /uri/user/#id#)
	 */
	void registerEndPoint(RestRequest::Method method, string uri, function<void (WebContext&)>  func);
	void handle(RestRequest &, RestResponse &);
};

#endif /* SRC_DISPATCHER_APIDISPATCHER_H_ */
