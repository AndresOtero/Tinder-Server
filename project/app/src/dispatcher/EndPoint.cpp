/*
 * EndPoint.cpp
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#include "EndPoint.h"
#include <regex>
#include "NoSuchMethodHandlerException.h"
using namespace std;


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
		PathVariableExtractor pv (this->uri, urireq);
		WebContext context(req, resp, pv);
		if(filter) {
			filter->filter(context, this->handler);
		} else {
			handler(context);
		}

	} else {
		if(this->next) {
			this->next->handle(req, resp);
		} else {
			throw NoSuchMethodHandlerException(req.toString());
		}
	}

}

EndPoint::~EndPoint() {
	if(this->next != 0) {
		delete this->next;
	}
}

EndPoint::EndPoint(string uri, function<void(WebContext &)> handler) {
	this->uri = uri;
	this->next = 0;
	regex exp ("#[^\\/]+#");
	const string replace = "([^\\/]+)";
	this->expression = "^" + regex_replace(uri, exp ,replace) + "$" ;
	this->handler = handler;
	this->filter = 0;
}

EndPoint::EndPoint(string uri, Filter &filter, function<void(WebContext &)> handler) {
	this->uri = uri;
	this->next = 0;
	regex exp ("#[^\\/]+#");
	const string replace = "([^\\/]+)";
	this->expression = "^" + regex_replace(uri, exp ,replace) + "$" ;
	this->handler = handler;
	this->filter = &filter;
}


