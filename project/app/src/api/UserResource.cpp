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
using namespace std;

UserResource::UserResource() {

}

void UserResource::setup(ApiDispatcher& dispatcher) {
    using placeholders::_1;
	dispatcher.registerEndPoint(RestRequest::GET, "/user/#id#", (function<void (WebContext&)>)bind( &UserResource::getUser, this, _1 ));

}

void UserResource::getUser(WebContext& context) {
	LOG_INFO << "prueba ok";
}

UserResource::~UserResource() {
}

