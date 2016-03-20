/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "mongoose.h"
#include "webserver/WebServer.h"
#include "dispatcher/EndPoint.h"
#include <boost/log/trivial.hpp>

int main() {
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
  WebServer ws;
  ws.start();

  return 0;
}
