/*
 * UserResource.cpp
 *
 *  Created on: 7 de abr. de 2016
 *      Author: jonathan
 */

#include <api/UserResource.h>
#include "webserver/RestRequest.h"
#include <functional>
#include "log/Logger.h"
#include "json/json/json.h"
#include "json/ParameterReader.h"
using namespace std;

UserResource::UserResource() {

}

void UserResource::setup(ApiDispatcher& dispatcher) {
    using placeholders::_1;
	dispatcher.registerEndPoint(RestRequest::GET, "/user/#id#", (function<void (WebContext&)>)bind( &UserResource::getUser, this, _1 ));
	dispatcher.registerEndPoint(RestRequest::POST, "/user/#id#", (function<void (WebContext&)>)bind( &UserResource::putUser, this, _1 ));

}

void UserResource::getUser(WebContext& context) {
	Json::Value value;
	Json::Value value2;
	value2["atributo"] = "prueba";
	value["root"] = value2;
	Json::FastWriter writer;
	context.getResponse().setContent(writer.write(value));
	context.getResponse().setContentType(CONTENT_TYPE_JSON);
}

void UserResource::putUser(WebContext& context) {
	string content = context.getRequest().getContent();
	Json::Reader reader;
	Json::Value parsed;
	bool parsingSuccessful = reader.parse(content, parsed);
	StringReader strreader(parsed["root"]);
	IntReader intrdr(parsed["root"]);
	LOG_INFO <<  strreader.get("tributo",false) << endl;
	LOG_INFO <<  intrdr.get("tributo2",false) << endl;
}

UserResource::~UserResource() {
}

