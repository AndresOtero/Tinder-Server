/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "mongoose.h"
#include "webserver/WebServer.h"
#include "dispatcher/EndPoint.h"

int main() {

  WebServer ws;
  ws.start();

  return 0;
}
