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


class EndPoint {
private:
	EndPoint * next;
	string expression;
	string uri;
	function<void(WebContext&)> handler;
public:
	EndPoint(string u, function<void(WebContext&)> handler);
	void setNext(EndPoint *);
	void handle(RestRequest &, RestResponse &);
	virtual ~EndPoint();
};

#endif /* SRC_DISPATCHER_ENDPOINT_H_ */
