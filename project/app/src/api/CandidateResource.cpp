//
// Created by matias on 5/23/16.
//

#include <UserNotFoundException.h>
#include <ServiceException.h>
#include "CandidateResource.h"
#include "ApiConstants.h"
#include <list>
#include <NoMoreCandidatesException.h>


CandidateResource::CandidateResource(MatchServices &services, ProfileServices &profile) : matchServices(services),
profileServices(profile) { }

CandidateResource::~CandidateResource() { }



void CandidateResource::setup(ApiDispatcher &dispatcher){
	using placeholders::_1;
	dispatcher.registerEndPoint(RestRequest::GET, "/candidates/#distancia#",
	                            (function<void (WebContext&)>)bind( &CandidateResource::getCandidates, this, _1 ));

}

void CandidateResource::getCandidates(WebContext &wc) {
	User *user;
	try {
		user = profileServices.getUserByID(wc.getUserid());
		std::list<User *> candidates = this->matchServices.getCandidatesForUser(user,
		                                                                        std::stoi(wc.getParam("distancia")));
		Json::Value result;
		result["candidates"] = Json::Value(Json::arrayValue);
		for(auto it = candidates.begin(); it != candidates.end(); ++it) {
			result["candidates"].append((*it)->toJson());
			delete (*it);
		}
		delete user;
		this->writeJsonResponse(wc, result);
	} catch (NoMoreCandidatesException & e) {
		Json::Value result;
		delete user;
		this->writeJsonResponse(wc, result, API_STATUS_USER_ALREADY_REQUESTED_CANDIDATES_TODAY);
	} catch (UserNotFoundException & e) {
		Json::Value result;
		this->writeJsonResponse(wc, result, API_STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED);
	} catch (ServiceException &e) {
		wc.getResponse().setStatus(STATUS_500_INTERNAL_SERVER_ERROR);
	}

}
