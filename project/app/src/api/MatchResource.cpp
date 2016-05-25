//
// Created by matias on 5/25/16.
//

#include <UserNotFoundException.h>
#include <ServiceException.h>
#include "MatchResource.h"
#include "ApiConstants.h"


MatchResource::MatchResource(MatchServices &matchServices, ProfileServices &profileServices) :
		matchServices(matchServices), profileServices(profileServices) { }

MatchResource::~MatchResource() { }

void MatchResource::setup(ApiDispatcher &dispatcher) {
	using placeholders::_1;
	dispatcher.registerEndPoint(RestRequest::GET, "/match",
	                            (function<void (WebContext&)>)bind( &MatchResource::getMatches, this, _1 ));
}

void MatchResource::getMatches(WebContext &wc) {
	User *user;
	try {
		user = profileServices.getUserByID(wc.getUserid());
		std::list<User *> matches = this->matchServices.getMatchesForUser(user);
		Json::Value result;
		result["matches"] = Json::Value(Json::arrayValue);
		for (auto it = matches.begin(); it != matches.end(); ++it) {
			result["matches"].append((*it)->toJson());
			delete (*it);
		}
		delete user;
		this->writeJsonResponse(wc, result);
	} catch (UserNotFoundException & e) {
		Json::Value result;
		this->writeJsonResponse(wc, result, API_STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED);
	} catch (ServiceException &e) {
		wc.getResponse().setStatus(STATUS_500_INTERNAL_SERVER_ERROR);
	}
}

