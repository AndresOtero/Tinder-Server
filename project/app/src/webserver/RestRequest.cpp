/*
 * RestRequest.cpp
 *
 *  Created on: 30 de mar. de 2016
 *      Author: jonathan
 */

#include <RestRequest.h>


string parseToToken(mg_str & str, string token) {
	std::string value (*(&str.p));
	std::size_t found = value.find(token);
	if (found!=std::string::npos)
		value = value.substr(0,found);
	return value;

}


RestRequest::RestRequest(http_message * hm) {
	this->message = hm;
	this->uri = parseToToken(hm->uri, URI_TOKEN);
    std::string data (*(&hm->body.p));
    this->content = data;
	parseHeaders();
}

RestRequest::~RestRequest() {
	// TODO Auto-generated destructor stub
}

string RestRequest::getUri() {
	return uri;
}


string RestRequest::toString() {
	 string method = parseToToken(this->message->method, METHOD_TOKEN);

	return method + ": " + this->getUri();
}

RestRequest::Method RestRequest::getMethod() {
	string method = parseToToken(this->message->method, METHOD_TOKEN);
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
	if(headers.count(name) > 0) {
		return headers[name];
	} else {
		return "";
	}

}

void RestRequest::parseHeaders() {
	bool end = false;
	for (int i = 0; i < MG_MAX_HTTP_HEADERS && !end; ++i) {
		mg_str & originalstr = this->message->header_names[i];
		if(originalstr.len > 0) {
			string currentName = parseToToken(originalstr, HEADER_NAME_TOKEN);
			this->headers.insert(std::make_pair(currentName, parseToToken(this->message->header_values[i], "\r")));
		} else {
			end = true;
		}
	}

}