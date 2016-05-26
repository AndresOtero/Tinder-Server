//
// Created by jonathan on 27/04/16.
//

#include <json/json.h>
#include <UserNotFoundException.h>
#include <ServiceException.h>
#include "InterestResource.h"
#include "ApiConstants.h"

InterestResource::InterestResource(ProfileServices &profileService): profileServices(profileService) {

}

void InterestResource::setup(ApiDispatcher & dispatcher) {
    using placeholders::_1;
    dispatcher.registerEndPoint(RestRequest::POST, "/interest",	(function<void(WebContext&)> )
            bind(&InterestResource::addInterest,this, _1));
    dispatcher.registerEndPoint(RestRequest::GET, "/interest",	(function<void(WebContext&)> )
            bind(&InterestResource::searchInterests,this, _1));
    dispatcher.registerEndPoint(RestRequest::DELETE, "/interest",	(function<void(WebContext&)> )
            bind(&InterestResource::removeInterest,this, _1));

}

void InterestResource::searchInterests(WebContext &wc) {
    const unordered_map<string, set<string>> map = profileServices.getInterests();
    Json::Value interests;
    for ( auto it = map.begin(); it != map.end(); ++it ) {
        for (set<string>::iterator setit = it->second.begin(); setit != it->second.end(); ++setit) {
            Json::Value valor;
            valor["category"] = it->first;
            valor["value"] = *setit;
            interests.append(valor);
        }
    }
    Json::Value result;
    result["interests"] = interests;
    RestResource::writeJsonResponse(wc, result);

}

void InterestResource::addInterest(WebContext &wc) {
    try {
        Json::Value json;
        RestResource::readJson(wc, json);
        Json::Value interests= json.get("interests", "");
        if(interests.isArray()) {
            list<Interest> interestsBuild= User::buildInterests(interests);
            string userid = wc.getUserid();
            profileServices.saveInterests(userid, interestsBuild);
            this->writeJsonResponse(wc, API_STATUS_CODE_DONE);
        } else {
            wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
        }
    } catch (UserNotFoundException & e) {
        Json::Value result;
         this->writeJsonResponse(wc, result, API_STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED);
    } catch (ServiceException &e) {
        wc.getResponse().setStatus(STATUS_500_INTERNAL_SERVER_ERROR);
    } catch (Json::LogicError) {
        wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
    }
}

void InterestResource::removeInterest(WebContext &wc) {
    try {
        Json::Value json;
        RestResource::readJson(wc, json);
        string category = json.get("category", "EMPTY FIELD").asString();
        string value = json.get("value", "EMPTY FIELD").asString();
        string userid = wc.getUserid();
        profileServices.removeInterest(userid, category, value);
        this->writeJsonResponse(wc, API_STATUS_CODE_DONE);
    } catch (UserNotFoundException & e) {
        Json::Value result;
         this->writeJsonResponse(wc, result, API_STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED);
    } catch (ServiceException &e) {
        wc.getResponse().setStatus(STATUS_500_INTERNAL_SERVER_ERROR);
    } catch (Json::LogicError) {
        wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
    }
}





