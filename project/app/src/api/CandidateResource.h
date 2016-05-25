//
// Created by matias on 5/23/16.
//

#ifndef TINDER_SERVER_CANDIDATERESOURCE_H
#define TINDER_SERVER_CANDIDATERESOURCE_H

#include "../services/match/MatchServices.h"
#include "dispatcher/RestResource.h"
#include "dispatcher/WebContext.h"
#include "dispatcher/ApiDispatcher.h"

/**
 * @class CandidateResource
 *
 * Provides functionality to get candidates for a user.
 */
class CandidateResource : public RestResource{
private:
	MatchServices& matchServices;
	ProfileServices profileServices;

public:
	CandidateResource(MatchServices &services, ProfileServices &profile);
	virtual ~CandidateResource();
	void setup(ApiDispatcher & dispatcher);
	void getCandidates(WebContext & wc);
};


#endif //TINDER_SERVER_CANDIDATERESOURCE_H
