/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include <User.h>
#include <ProfileServices.h>
#include "webserver/WebServer.h"
#include "log/Logger.h"
#include "db/DBConnector.h"
#include "dispatcher/ApiDispatcher.h"
#include "api/UserResource.h"
#include "api/AuthResource.h"
#include "services/authentication/AuthenticationService.h"

int main() {
	LOG_INFO << "Testing conection to shared server.";
	SharedConnector sharedConnector = SharedConnector("http://tinder-shared.herokuapp.com");
	if(!sharedConnector.testConnection()) LOG_ERROR << "Error probando conexion con el shared server";
	else LOG_INFO << "CONNECTION [OK]";


	LOG_INFO << "Starting DB";
	DBConnector connector = DBConnector("/tmp/testdb/");
	if(!connector.isOk()) LOG_ERROR << ("Error abriendo la DB.");


	LOG_INFO << "Starting WebServer";
	ApiDispatcher dispatcher;
	UserResource user;
	user.setup(dispatcher);
	AuthenticationService authService(&connector);
	AuthResource auth (&authService);

	auth.setup(dispatcher);
	WebServer ws(dispatcher);

	ws.start();
	return 0;

}
