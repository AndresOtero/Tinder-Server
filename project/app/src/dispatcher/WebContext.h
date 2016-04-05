/*
 * WebContext.h
 *
 *  Created on: 30 de mar. de 2016
 *      Author: jonathan
 */

#ifndef APP_SRC_DISPATCHER_WEBCONTEXT_H_
#define APP_SRC_DISPATCHER_WEBCONTEXT_H_
#include "webserver/RestRequest.h"
#include "webserver/RestResponse.h"
#include "PathVariableExtractor.h"
#include <map>
#include <string>
using namespace std;

class WebContext {

private:
	map<string, string> uriparams;
	RestRequest * request;
	RestResponse * response;
	PathVariableExtractor * pv;
public:
	WebContext(RestRequest&, RestResponse&, PathVariableExtractor &);
	virtual ~WebContext();
};

#endif /* APP_SRC_DISPATCHER_WEBCONTEXT_H_ */
