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

UserResource::UserResource(ProfileServices & services): service(service)  {

}

void UserResource::setup(ApiDispatcher& dispatcher) {
    using placeholders::_1;
	dispatcher.registerEndPoint(RestRequest::GET, "/user", (function<void (WebContext&)>)bind( &UserResource::getUser, this, _1 ));
	dispatcher.registerEndPoint(RestRequest::POST, "/user", (function<void (WebContext&)>)bind( &UserResource::putUser, this, _1 ));

}

void UserResource::getUser(WebContext& context) {
	User * user = service.getUserByID(context.getUserid());
	Json::Value result = user->toJson();
	delete user;
	Json::FastWriter writer;
	context.getResponse().setContent(writer.write(result));
}

void UserResource::putUser(WebContext& context) {
	Json::Value json;

	RestResource::readJson(context, json);
	User user(json);
	user.setId(context.getUserid());
	/*service.saveNewUser()*/
}

UserResource::~UserResource() {
}

