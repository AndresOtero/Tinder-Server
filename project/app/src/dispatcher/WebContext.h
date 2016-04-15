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
#include <string>
using namespace std;

/**
 * @class WebContext
 *
 *
 * @author jtierno

 * Represents the Context arround a Rest API Request
 */

class WebContext {

private:
	/**
	 * Information in the Request
	 */
	RestRequest * request;

	/**
	 * Information that will be written in the response
	 */
	RestResponse * response;

	/**
	 * Variables in uri reader
	 */
	PathVariableExtractor * pv;
public:
	/**
	 * Constructor with dependencies.
	 * @param request Information in the Request
	 * @param response Where to build the answer
	 * @param pv from where obtain variables of uri
	 */
	WebContext(RestRequest& request, RestResponse& response, PathVariableExtractor & pv);

	/**
	 * Obtain a parameter of uri
	 * @param name Name of variable
	 * @return A string with value if exists, else an empty string
	 */
	string getParam(string name);

	/**
	 * Getter of Request
	 * @return the Request
	 */
	RestRequest & getRequest();

	/**
	 * Getter of Response
	 * @return the Response
	 */

	RestResponse & getResponse();
	virtual ~WebContext();
};

#endif /* APP_SRC_DISPATCHER_WEBCONTEXT_H_ */
