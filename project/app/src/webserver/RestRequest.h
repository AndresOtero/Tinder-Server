/*
 * RestRequest.h
 *
 *  Created on: 30 de mar. de 2016
 *      Author: jonathan
 */

#ifndef APP_SRC_WEBSERVER_RESTREQUEST_H_
#define APP_SRC_WEBSERVER_RESTREQUEST_H_
#include "string"
#include <map>
using namespace std;

class RestRequest {
private:
	string uri;



public:
	RestRequest();
	virtual ~RestRequest();
	string getUri();
	string otro();
	void setUri(string uri);
};

#endif /* APP_SRC_WEBSERVER_RESTREQUEST_H_ */
