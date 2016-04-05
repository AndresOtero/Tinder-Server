/*
 * EndPoint.cpp
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#include "EndPoint.h"
#include <regex>
#include <iostream>
#include <string>
#include "../webserver/RestRequest.h"
#include "../webserver/RestResponse.h"
#include "log/Logger.h"
#include "NoSuchMethodHandlerException.h"

using namespace std;


EndPoint::EndPoint(string u) {

		this->uri = u;
		this->next = 0;
		regex exp ("#[^\\/]+#");
		const string replace = "([^\\/]+)";
		this->expression = "^" + regex_replace(u, exp ,replace) + "$" ;
}

void EndPoint::setNext(EndPoint* next) {
 if(this->next == 0) {
	 this->next = next;
 } else {
	 this->next->setNext(next);
 }
}

void EndPoint::handle(RestRequest & req, RestResponse & resp) {
	regex exp (this->expression);
	string urireq = req.getUri();

	if(regex_match(urireq, exp)) {

	} else {
		if(this->next) {
			this->next->handle(req, resp);
		} else {
			throw NoSuchMethodHandlerException(urireq);
		}
	}

}

EndPoint::~EndPoint() {
	if(this->next != 0) {
		delete this->next;
	}
}

