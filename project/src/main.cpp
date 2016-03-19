/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "mongoose.h"
#include "webserver/WebServer.h"


int main(int argc, char *argv[]) {

  WebServer ws;
  ws.start();

  return 0;
}
