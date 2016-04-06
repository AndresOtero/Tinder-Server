/*
 * ApiDispatcher.cpp
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#include "ApiDispatcher.h"
#include "NoSuchMethodHandlerException.h"


ApiDispatcher::ApiDispatcher() {
	this->defFunction = [](WebContext & wb){
		throw NoSuchMethodHandlerException(wb.getRequest().toString());
	};
	this->endpoints.insert(std::make_pair(RestRequest::GET, new EndPoint("/////", this->defFunction)));
	this->endpoints.insert(std::make_pair(RestRequest::DEL, new EndPoint("/////", this->defFunction)));
	this->endpoints.insert(std::make_pair(RestRequest::PUSH, new EndPoint("/////", this->defFunction)));
	this->endpoints.insert(std::make_pair(RestRequest::PUT, new EndPoint("/////", this->defFunction)));

}

ApiDispatcher::~ApiDispatcher() {
}

void ApiDispatcher::registerEndPoint(RestRequest::Method method, string uri, function<void(WebContext&)> & handler) {

}

void ApiDispatcher::handle(RestRequest&, RestResponse&) {

}
