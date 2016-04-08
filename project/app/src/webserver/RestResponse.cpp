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
	// TODO Auto-generated destructor stub
}

void RestResponse::setStatus(string status) {
	this->status = status;
}

string RestResponse::getStatus() {
	return status;
}

void RestResponse::render(mg_connection* nc) {
	mg_printf(nc, "HTTP/1.1 %s \r\nContent-Length: 0\r\n\r\n", status.c_str());
}
