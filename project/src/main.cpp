/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "mongoose.h"
#include "app/webserver/WebServer.h"
#include "app/dispatcher/EndPoint.h"
#include "app/log/Logger.h"

int main() {
 Logger logger;
 logger.info("Starting WebServer");
  WebServer ws;
  ws.start();

  return 0;
}
