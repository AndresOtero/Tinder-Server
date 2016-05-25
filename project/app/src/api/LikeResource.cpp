//
// Created by matias on 5/25/16.
//

#include <UserNotFoundException.h>
#include <ServiceException.h>
#include "LikeResource.h"
#include "ApiConstants.h"


LikeResource::LikeResource(MatchServices &matchServices, ProfileServices &profileServices) :
		profileServices(profileServices), matchServices(matchServices) { }

LikeResource::~LikeResource() { }

void LikeResource::setup(ApiDispatcher &dispatcher) {
	using placeholders::_1;
	dispatcher.registerEndPoint(RestRequest::GET, "/like",
	                            (function<void (WebContext&)>)bind( &LikeResource::getLikes, this, _1 ));
	dispatcher.registerEndPoint(RestRequest::POST, "/like",
	                            (function<void (WebContext&)>)bind( &LikeResource::likeUser, this, _1 ));
}

void LikeResource::getLikes(WebContext &wc) {
	User *user;
	try {
		user = profileServices.getUserByID(wc.getUserid());
		std::list<User *> likes = this->matchServices.getLikesForUser(user);
		Json::Value result;
		result["likes"] = Json::Value(Json::arrayValue);
		for (auto it = likes.begin(); it != likes.end(); ++it) {
			result["likes"].append((*it)->toJson());
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

void LikeResource::likeUser(WebContext &wc) {
	User *user;
	try {
		user = profileServices.getUserByID(wc.getUserid());
	} catch (UserNotFoundException & e) {
		wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
	} catch (ServiceException &e) {
		wc.getResponse().setStatus(STATUS_500_INTERNAL_SERVER_ERROR);
	}
	User* liked;
	try {
		Json::Value json;
		RestResource::readJson(wc, json);
		string likedId = json.get("likedUser", "EMPTY FIELD").asString();
		liked = this->profileServices.getUserByID(likedId);
		this->matchServices.likeAUser(user, liked);
		delete liked;
		delete user;
		this->writeJsonResponse(wc);
	} catch (UserNotFoundException & e) {
		delete user;
		wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
	}
}

