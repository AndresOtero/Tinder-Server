//
// Created by jonathan on 25/05/16.
//

#include "WebServerException.h"


WebServerException::WebServerException(const string msg) : runtime_error(msg){ }

WebServerException::~WebServerException() { }