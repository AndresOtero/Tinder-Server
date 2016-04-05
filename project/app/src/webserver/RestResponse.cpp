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

void RestResponse::render(mg_connection* nc) {
}
