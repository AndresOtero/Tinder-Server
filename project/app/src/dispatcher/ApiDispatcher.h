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

class ApiDispatcher: public RequestDispatcher {
private:
	map<RestRequest::Method, EndPoint *> endpoints;
	function<void(WebContext&)> defFunction;
public:
	ApiDispatcher();
	virtual ~ApiDispatcher();
	void registerEndPoint(RestRequest::Method method, string uri, function<void (WebContext&)> & func);
	void handle(RestRequest &, RestResponse &);
};

#endif /* SRC_DISPATCHER_APIDISPATCHER_H_ */
