/*
 * AuthResource.cpp
 *
 *  Created on: 10 de abr. de 2016
 *      Author: jonathan
 */

#include <api/AuthResource.h>
#include <functional>
#include <string>
#include "json/ParameterReader.h"
#include "services/authentication/JsonWebToken.h"
#include "log/Logger.h"
using namespace std;

AuthResource::AuthResource(AuthenticationService* service) {
	this->service = service;
}

void AuthResource::setup(ApiDispatcher& dispatcher) {
	using placeholders::_1;
	dispatcher.registerEndPoint(RestRequest::POST, "/auth",	(function<void(WebContext&)> ) bind(&AuthResource::authenticate,this, _1));

}

void AuthResource::authenticate(WebContext& wc) {
	string content = wc.getRequest().getContent();
	Json::Reader reader;
	Json::Value parsed;
	bool parsingSuccessful = reader.parse(content, parsed);
	if (parsingSuccessful) {
		try {
			StringReader strreader(parsed);
			string user = strreader.get("user", true);
			string password = strreader.get("password", true);
			bool authenticated = this->service->isLoginValid(user, password);
			if (authenticated) {
				JsonWebToken jwt;
				string token = jwt.generateTokenForUser(user);
				wc.getResponse().setContent("{\"token\": \"" + token + "\"}");
				wc.getResponse().setStatus(STATUS_200_OK);
			} else {
				wc.getResponse().setStatus(STATUS_401_UNAUTHORIZED);
			}
		} catch (string & e) {
			LOG_DEBUG<< e;

		}
	} else {
		wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
	}
}

AuthResource::~AuthResource() {
	// TODO Auto-generated destructor stub
}

