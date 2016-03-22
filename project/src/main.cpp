/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "mongoose.h"
#include "webserver/WebServer.h"
#include "dispatcher/EndPoint.h"
#include "log/Logger.h"
#include "db/DBConnector.h"

int main() {
	 Logger logger;
	 logger.info("Starting WebServer");
	 logger.info("Starting DB");
	 DBConnector connector = DBConnector("/tmp/testdb/");
	 if(!connector.isOk()) logger.error("Error abriendo la DB.");
	 WebServer ws;
	 ws.start();

	 return 0;
}
