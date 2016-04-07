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
	this->endpoints.insert(std::make_pair(RestRequest::DELETE, new EndPoint("/////", this->defFunction)));
	this->endpoints.insert(std::make_pair(RestRequest::POST, new EndPoint("/////", this->defFunction)));
	this->endpoints.insert(std::make_pair(RestRequest::PUT, new EndPoint("/////", this->defFunction)));

}

ApiDispatcher::~ApiDispatcher() {
}

void ApiDispatcher::registerEndPoint(RestRequest::Method method, string uri, function<void(WebContext&)> & handler) {

}

void ApiDispatcher::handle(RestRequest& request, RestResponse& response) {
	RestRequest::Method method = request.getMethod();
	if (this->endpoints.count(method) > 0) {
		this->endpoints[method]->handle(request,response);
	}
	else throw NoSuchMethodHandlerException(request.toString());
}
