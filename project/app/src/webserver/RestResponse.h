/*
 * RestResponse.h
 *
 *  Created on: 30 de mar. de 2016
 *      Author: jonathan
 */

#ifndef APP_SRC_WEBSERVER_RESTRESPONSE_H_
#define APP_SRC_WEBSERVER_RESTRESPONSE_H_

#include <string>
#include "mongoose/mongoose.h"
#include "Constants.h"
using namespace std;




class RestResponse {
private:
	string status;
	string body;
	string contentType;
public:

	RestResponse();
	virtual ~RestResponse();
	void setStatus(string status);
	void setContent(string body);
	void setContentType(string contentyType);
	string getStatus();
	void render (mg_connection *nc);
};

#endif /* APP_SRC_WEBSERVER_RESTRESPONSE_H_ */
