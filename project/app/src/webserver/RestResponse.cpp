/*
 * RestResponse.cpp
 *
 *  Created on: 30 de mar. de 2016
 *      Author: jonathan
 */

#include <RestResponse.h>

RestResponse::RestResponse() {
}

RestResponse::~RestResponse() {
}

void RestResponse::setStatus(string status) {
	this->status = status;
}

string RestResponse::getStatus() {
	return status;
}

void RestResponse::setContent(string body) {
	this->body = body;
}

void RestResponse::render(mg_connection* nc) {
	int size = this->body.size();
	mg_printf(nc, "HTTP/1.1 %s \r\nContent-Length: %i\r\n\r\n", status.c_str(), size);
	mg_printf(nc, "%s", body.c_str());
}
