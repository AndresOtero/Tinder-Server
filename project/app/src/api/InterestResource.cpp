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
    dispatcher.registerEndPoint(RestRequest::GET, "/interest/#interest#",	(function<void(WebContext&)> )
            bind(&InterestResource::searchInterests,this, _1));
    dispatcher.registerEndPoint(RestRequest::DELETE, "/interest",	(function<void(WebContext&)> )
            bind(&InterestResource::removeInterest,this, _1));

}

void InterestResource::searchInterests(WebContext &wc) {
    const string interest = wc.getParam("interest");
    if(interest.size() == 0) {
        wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
    }


}

void InterestResource::addInterest(WebContext &wc) {
    Json::Value json = RestResource::readJson(wc);
    string category = json.get("category", "EMPTY FIELD").asString();
    string value = json.get("value", "EMPTY FIELD").asString();
    int userid = wc.getUserid();
    profileServices.addInterest(userid, category, value);

}

void InterestResource::removeInterest(WebContext &wc) {
    Json::Value json = RestResource::readJson(wc);
    string category = json.get("category", "EMPTY FIELD").asString();
    string value = json.get("value", "EMPTY FIELD").asString();
    int userid = wc.getUserid();
    profileServices.removeInterest(userid, category, value);
}





