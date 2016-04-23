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
    std::string data (*(&hm->body.p));
    this->content = data;
}

RestRequest::~RestRequest() {
	// TODO Auto-generated destructor stub
}

string RestRequest::getUri() {
	return uri;
}

string parseMethod(	http_message * message) {
	std::string method (*(&message->method.p));
	 std::size_t found = method.find(" ");
	 if (found!=std::string::npos)
	    method = method.substr(0,found);
	 return method;
}

string RestRequest::extractUri(http_message* hm) {
	  string uri (*(&hm->uri.p));
	  std::size_t found = uri.find(" ");
	   if (found!=std::string::npos)
	     uri = uri.substr(0,found);
	   return uri;
}

string RestRequest::toString() {
	 string method = parseMethod(this->message);

	return method + ": " + this->getUri();
}

RestRequest::Method RestRequest::getMethod() {
	string method = parseMethod(this->message);
	if( method == "GET") return GET;
	if( method == "PUT") return PUT;
	if( method == "POST") return POST;
	if( method == "DELETE") return DELETE;
	return UNKNOWN;

}

string RestRequest::getContent() {
	return this->content;
}

string RestRequest::getDescription(RestRequest::Method method) {
	switch (method) {
		case PUT:
			return "PUT";
		case POST:
			return "POST";
		case GET:
			return "GET";
		case DELETE:
			return "DELETE";
		default:
			return "";
	}
}

string RestRequest::getHeader(string name) {
	bool found = false;
	string result = "";
	int i;
	for (i = 0; i < MG_MAX_HTTP_HEADERS && !found; ++i) {
		string currentName (*(&this->message->header_names[i].p));
		if(currentName == name ){
			string val(*(&this->message->header_names[i].p));
			result = val;
			found = true;
		}
	}
	return result;
}