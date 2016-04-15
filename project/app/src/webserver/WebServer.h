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


/**
 * @class WebServer
 * Handles incoming web connections
 *
 * @author jtierno
 *
 */

class WebServer {
private :
	/**
	 * Web connection
	 */
	struct mg_connection * connection;

	/**
	 * Where to dispatches api requests
	 */
	RequestDispatcher * dispatcher;
public:
	/**
	 * Constructor with api dispatcher that handles requests
	 * @param dispatcher The Dispatcher
	 */
	WebServer(RequestDispatcher & dispatcher);
	virtual ~WebServer();

	/**
	 * Starts server to listen web requests
	 */
	void start();

	/**
	 * Gets dispatcher
	 * @return dispatcher
	 */
	RequestDispatcher* getDispatcher() ;
};

#endif /* SRC_WEBSERVER_WEBSERVER_H_ */
