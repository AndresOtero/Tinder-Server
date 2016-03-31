/*
 * WebServer.h
 *
 *  Created on: 18 de mar. de 2016
 *      Author: jonathan
 */

#ifndef SRC_WEBSERVER_WEBSERVER_H_
#define SRC_WEBSERVER_WEBSERVER_H_



#include "mongoose/mongoose.h"
#include "dispatcher/ApiDispatcher.h"
#include <string>
using namespace std;


class WebServer {
private :
	struct mg_connection * connection;
	ApiDispatcher * dispatcher;
public:
	WebServer(ApiDispatcher &);
	virtual ~WebServer();
	void start();

	string getUri(http_message *);
};

#endif /* SRC_WEBSERVER_WEBSERVER_H_ */
