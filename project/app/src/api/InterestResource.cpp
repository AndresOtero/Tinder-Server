//
// Created by jonathan on 27/04/16.
//

#include <json/json.h>
#include "InterestResource.h"

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
    RestResource::writeJson(wc, result);
}

void InterestResource::addInterest(WebContext &wc) {
    Json::Value json;
    RestResource::readJson(wc, json);
    string category = json.get("category", "EMPTY FIELD").asString();
    string value = json.get("value", "EMPTY FIELD").asString();
    string userid = wc.getUserid();
    profileServices.addInterest(userid, category, value);

}

void InterestResource::removeInterest(WebContext &wc) {
    Json::Value json;
    RestResource::readJson(wc, json);
    string category = json.get("category", "EMPTY FIELD").asString();
    string value = json.get("value", "EMPTY FIELD").asString();
    string userid = wc.getUserid();
    profileServices.removeInterest(userid, category, value);
}





