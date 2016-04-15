/*
  @file EndPoint.h
 
   Created on: 19 de mar. de 2016
       @Author: jonathan
 */

#ifndef SRC_DISPATCHER_ENDPOINT_H_
#define SRC_DISPATCHER_ENDPOINT_H_
#include <string>
#include <functional>
#include "mongoose/mongoose.h"
#include "webserver/RestRequest.h"
#include "webserver/RestResponse.h"
#include "WebContext.h"
using namespace std;


/**
 * @class EndPoint
 * This Class builds a correct path for handling requests, by a chain of Responsability
 *
 * @author jtierno
 *
 */
class EndPoint {
private:
	/**
	 * Next EndPoint where to dispatch a request that cannot be handled by this endpoint
	 */
	EndPoint * next;
	/**
	 * Expression to be evaluated for matching uri in request
	 */
	string expression;
	/*
	 * Original uri
	 */
	string uri;

	/**
	 * Handler for this enpoint
	 */
	function<void(WebContext&)> handler;
public:
	/**
	 * Constructor with uri to handle
	 * @param uri uri to be handled
	 * @param handler function that handle the uri
	 */
	EndPoint(string uri, function<void(WebContext&)> handler);

	/**
	 * Set next EndPoint in chain
	 *
	 * @param next next Endpoint in chain
	 */
	void setNext(EndPoint * next);

	/**
	 * Handle a specific Request if match with this Endpoint, if not delegates to next Endpoint
	 *
	 *@param request request information
	 *@param response where set response data
	 */
	void handle(RestRequest & request, RestResponse & response);
	virtual ~EndPoint();
};

#endif /* SRC_DISPATCHER_ENDPOINT_H_ */
