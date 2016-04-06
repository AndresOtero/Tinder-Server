/*
 * RestRequest.cpp
 *
 *  Created on: 30 de mar. de 2016
 *      Author: jonathan
 */

#include <RestRequest.h>

RestRequest::RestRequest(http_message * hm) {
	this->message = hm;
	this->uri = extractUri(hm);

}

RestRequest::~RestRequest() {
	// TODO Auto-generated destructor stub
}

string RestRequest::getUri() {
	return uri;
}


string RestRequest::extractUri(http_message* hm) {
	  string uri (*(&hm->uri.p));
	  std::size_t found = uri.find(" ");
	   if (found!=std::string::npos)
	     uri = uri.substr(0,found);
	   return uri;
}

string RestRequest::toString() {
	std::string method (*(&message->method.p));
	return method + ": " + this->getUri();
}
