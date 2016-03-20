/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "mongoose.h"
#include "webserver/WebServer.h"
#include "dispatcher/EndPoint.h"
#include "log/Logger.h"

int main() {
 Logger logger;
 logger.info("Starting WebServer");
  WebServer ws;
  ws.start();

  return 0;
}
