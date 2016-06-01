/*
 * AuthResource.cpp
 *
 *  Created on: 10 de abr. de 2016
 *      Author: jonathan
 */

#include <api/AuthResource.h>
#include <functional>
#include <string>
#include <ServiceException.h>
#include "json/ParameterReader.h"
#include "JsonWebToken.h"
#include "log/Logger.h"
#include "ApiConstants.h"

using namespace std;
static const string LOG_PREFIX = "AuthResource: ";

AuthResource::AuthResource(AuthenticationService *service) {
    this->service = service;
}

void AuthResource::setup(ApiDispatcher &dispatcher) {
    using placeholders::_1;
    dispatcher.registerEndPoint(RestRequest::PUT, "/auth",
                                (function<void(WebContext &)>) bind(&AuthResource::authenticate, this, _1));
    dispatcher.registerEndPoint(RestRequest::POST, "/auth",
                                (function<void(WebContext &)>) bind(&AuthResource::create, this, _1));
    dispatcher.registerEndPoint(RestRequest::DELETE, "/auth",
                                (function<void(WebContext &)>) bind(&AuthResource::remove, this, _1));

}

void AuthResource::authenticate(WebContext &wc) {
        Json::Value parsed;
        this->readJson(wc, parsed);
        string user = parsed.get("user", "").asString();
        string password = parsed.get("password", "").asString();
        bool authenticated = this->service->isLoginValid(user, password);
        if (authenticated) {
            JsonWebToken jwt;
            Json::Value json;
            json[SECURITY_TOKEN_PARAM] = jwt.generateTokenForUser(user);
            this->writeJsonResponse(wc, json);
        } else {
            wc.getResponse().setStatus(STATUS_401_UNAUTHORIZED);
        }
}

AuthResource::~AuthResource() {
}

void AuthResource::create(WebContext &wc) {
    try {
        Json::Value parsed;
        this->readJson(wc, parsed);
        string user = parsed.get("user", "").asString();
        string password = parsed.get("password", "").asString();
        bool requiredUser = this->service->saveNewUser(user, password);
        Json::Value json;

        JsonWebToken jwt;
        string token = jwt.generateTokenForUser(user);
        json[SECURITY_TOKEN_PARAM] = token;

        if (requiredUser) {
            this->writeJsonResponse(wc, json, API_STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED);
        } else {
            this->writeJsonResponse(wc, json);
        }

    } catch (AuthenticationException &e) {
        wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
        LOG_DEBUG << LOG_PREFIX << "Error creating user " << e.what();
        this->writeJsonResponse(wc, API_STATUS_USER_ALREADY_EXIST);
    } catch (ServiceException & e) {
        LOG_DEBUG << LOG_PREFIX << "Error creating user " << e.what();
        wc.getResponse().setStatus(STATUS_500_INTERNAL_SERVER_ERROR);
    }

}

void AuthResource::remove(WebContext &wc) {
    try {
        Json::Value parsed;
        this->readJson(wc, parsed);
        string password = parsed.get("password", "").asString();
        service->deleteUser(wc.getUserid(), password);
        this->writeJsonResponse(wc);
    } catch (AuthenticationException const & e) {
        LOG_DEBUG << LOG_PREFIX << "Error deleting user " << e.what();
        wc.getResponse().setStatus(STATUS_401_UNAUTHORIZED);
    } catch (ServiceException & e) {
        LOG_DEBUG << LOG_PREFIX << "Error deleting user " << e.what();
        wc.getResponse().setStatus(STATUS_500_INTERNAL_SERVER_ERROR);
    }

}


