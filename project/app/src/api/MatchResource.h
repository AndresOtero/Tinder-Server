//
// Created by matias on 5/25/16.
//

#ifndef TINDER_SERVER_MATCHRESOURCE_H
#define TINDER_SERVER_MATCHRESOURCE_H

#include "../services/match/MatchServices.h"
#include "dispatcher/RestResource.h"
#include "dispatcher/WebContext.h"
#include "dispatcher/ApiDispatcher.h"

class MatchResource : public RestResource {
public:
	MatchResource(MatchServices& matchServices, ProfileServices& profileServices);
	virtual ~MatchResource();
	void setup(ApiDispatcher & dispatcher);
	void getMatches(WebContext & wc);

private:
	ProfileServices profileServices;
	MatchServices matchServices;
};


#endif //TINDER_SERVER_MATCHRESOURCE_H
