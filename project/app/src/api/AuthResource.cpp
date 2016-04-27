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
#include "ApiConstants.h"
using namespace std;
static const string LOG_PREFIX = "AuthResource: ";

AuthResource::AuthResource(AuthenticationService* service) {
	this->service = service;
}

void AuthResource::setup(ApiDispatcher& dispatcher) {
	using placeholders::_1;
	dispatcher.registerEndPoint(RestRequest::PUT, "/auth",	(function<void(WebContext&)> ) bind(&AuthResource::authenticate,this, _1));
	dispatcher.registerEndPoint(RestRequest::POST, "/auth",	(function<void(WebContext&)> ) bind(&AuthResource::create,this, _1));

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
				wc.getResponse().setContent("{\""+SECURITY_TOKEN_PARAM +"\": \"" + token + "\"}");
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

//devuelve el token y si es necesario crear un profile().
void AuthResource::create(WebContext & wc) {
	string content = wc.getRequest().getContent();
	Json::Reader reader;
	Json::Value parsed;
	bool parsingSuccessful = reader.parse(content, parsed);
	if (parsingSuccessful) {
		try {
			StringReader strreader(parsed);
			string user = strreader.get("user", true);
			string password = strreader.get("password", true);
			this->service->saveNewUser(user, password);
			JsonWebToken jwt;
			string token = jwt.generateTokenForUser(user);
			//TODO CUANDO ESTÉ LO DE MATY SETEAR UN STATUS CODE O NO
			Json::Value json;
			json[STATUS_CODE_PARAM] = STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED;
			json[SECURITY_TOKEN_PARAM] = token;
			Json::FastWriter writer;
			wc.getResponse().setContent(writer.write(json));

		} catch (string & e) {
			LOG_DEBUG<< LOG_PREFIX << "Error parsing request " << e;
			wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
		} catch (AuthenticationException & e) {
			LOG_DEBUG<< LOG_PREFIX<< "Error creating user " << e.what();
			wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
			Json::Value result;
			result["error"] = e.what();
			Json::FastWriter writer;
			wc.getResponse().setContent(writer.write(result));
		}
	} else {
		wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
	}
}