/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "webserver/WebServer.h"
#include "log/Logger.h"
#include "db/DBConnector.h"
#include "dispatcher/ApiDispatcher.h"
#include "sharedConnector/SharedConnector.h"

int main() {
	 Logger logger;

	 logger.info("Testing conecction to shared server.");
	 SharedConnector sharedConnector = SharedConnector("http://tinder-shared.herokuapp.com");
	 if(!sharedConnector.testConnection()) logger.error("Error probando conexion con el shared server");
	 else logger.info("CONNECTION [OK]");

	 logger.info("Starting DB");
	 DBConnector dbconnector = DBConnector("/tmp/testdb/");
	 if(!dbconnector.isOk()) logger.error("Error abriendo la DB.");
	 else logger.info("DB [OK]");

	 logger.info("Starting WebServer");
	 ApiDispatcher dispatcher;
	 WebServer ws(dispatcher);
	 ws.start();

	 return 0;
}
