/*
 * RestRequest.h
 *
 *  Created on: 30 de mar. de 2016
 *      Author: jonathan
 */

#ifndef APP_SRC_WEBSERVER_RESTREQUEST_H_
#define APP_SRC_WEBSERVER_RESTREQUEST_H_
#include <string>
#include <map>
#include "mongoose/mongoose.h"
using namespace std;

class RestRequest {
private:
	string uri;
	http_message * message;
	string extractUri(http_message* hm);


public:
	RestRequest(http_message *);
	virtual ~RestRequest();
	string getUri();
	enum Method {GET, PUT, POST, DELETE};
	string toString();
	Method getMethod();
	static string getDescription(RestRequest::Method);
};

#endif /* APP_SRC_WEBSERVER_RESTREQUEST_H_ */
