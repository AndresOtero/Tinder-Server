/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "webserver/WebServer.h"
#include "log/Logger.h"
#include "db/DBConnector.h"
#include "dispatcher/ApiDispatcher.h"

int main() {
	 LOG_INFO << "Starting WebServer";
	 LOG_INFO << "Starting DB";
	 DBConnector connector = DBConnector("/tmp/testdb/");
	 if(!connector.isOk()) LOG_ERROR << ("Error abriendo la DB.");
	 ApiDispatcher dispatcher;
	 WebServer ws(dispatcher);
	 ws.start();

	 return 0;
}
