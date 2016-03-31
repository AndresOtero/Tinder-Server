/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "webserver/WebServer.h"
#include "log/Logger.h"
#include "db/DBConnector.h"
#include "dispatcher/ApiDispatcher.h"

int main() {
	 Logger logger;
	 logger.info("Starting WebServer");
	 logger.info("Starting DB");
	 DBConnector connector = DBConnector("/tmp/testdb/");
	 if(!connector.isOk()) logger.error("Error abriendo la DB.");
	 ApiDispatcher dispatcher;
	 WebServer ws(dispatcher);
	 ws.start();

	 return 0;
}
