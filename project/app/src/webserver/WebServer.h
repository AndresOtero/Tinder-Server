/*
 * WebServer.h
 *
 *  Created on: 18 de mar. de 2016
 *      Author: jonathan
 */

#ifndef SRC_WEBSERVER_WEBSERVER_H_
#define SRC_WEBSERVER_WEBSERVER_H_
#include <string>

#include "../mongoose/mongoose.h"
using namespace std;


class WebServer {
public:
	WebServer();
	virtual ~WebServer();
	void start();
	string getUri(http_message *);
private :
	struct mg_connection * connection;
private :
};

#endif /* SRC_WEBSERVER_WEBSERVER_H_ */
