/*
 * WebServer.h
 *
 *  Created on: 18 de mar. de 2016
 *      Author: jonathan
 */

#ifndef SRC_WEBSERVER_WEBSERVER_H_
#define SRC_WEBSERVER_WEBSERVER_H_



#include "mongoose/mongoose.h"
#include "RequestDispatcher.h"
#include <string>
using namespace std;


class WebServer {
private :
	struct mg_connection * connection;
	RequestDispatcher * dispatcher;
public:
	WebServer(RequestDispatcher &);
	virtual ~WebServer();
	void start();
	RequestDispatcher* getDispatcher() ;
};

#endif /* SRC_WEBSERVER_WEBSERVER_H_ */
