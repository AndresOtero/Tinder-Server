//
// Created by jonathan on 23/05/16.
//

#include <UserNotFoundException.h>
#include <ServiceException.h>
#include "LocationResource.h"
#include "ApiConstants.h"

LocationResource::LocationResource(ProfileServices &service): service(service) {

}

LocationResource::~LocationResource() {

}

void LocationResource::setup(ApiDispatcher &dispatcher) {
    using placeholders::_1;
    dispatcher.registerEndPoint(RestRequest::POST, "/location",
                                (function<void(WebContext &)>) bind(&LocationResource::updateLocation, this, _1));
}

void LocationResource::updateLocation(WebContext & context) {
    try {
        string username = context.getUserid();
        Json::Value parsed;
        RestResource::readJson(context, parsed);
        double latitude = parsed.get("latitude", "").asDouble();
        double longitude = parsed.get("longitude", "").asDouble();
        this->service.updateLocation(username, latitude, longitude);
        this->writeJsonResponse(context);
    } catch (UserNotFoundException & e) {
        Json::Value result;
         this->writeJsonResponse(context, result, API_STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED);
    } catch (ServiceException &e) {
        context.getResponse().setStatus(STATUS_500_INTERNAL_SERVER_ERROR);
    } catch (Json::LogicError) {
        context.getResponse().setStatus(STATUS_400_BAD_REQUEST);
    }
}







