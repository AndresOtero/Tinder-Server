//
// Created by matias on 5/25/16.
//

#ifndef TINDER_SERVER_LIKERESOURCE_H
#define TINDER_SERVER_LIKERESOURCE_H

#include "../services/match/MatchServices.h"
#include "dispatcher/RestResource.h"
#include "dispatcher/WebContext.h"
#include "dispatcher/ApiDispatcher.h"

/**
 * @class LikeResource
 * Provices functionality to see previous likes and save new ones.
 *
 * @author MLuraschi
 */
class LikeResource : public RestResource{
public:
	LikeResource(MatchServices& matchServices, ProfileServices& profileServices);
	virtual ~LikeResource();
	void setup(ApiDispatcher & dispatcher);
	void getLikes(WebContext & wc);
	void likeUser(WebContext & wc);

private:
	ProfileServices profileServices;
	MatchServices matchServices;

};


#endif //TINDER_SERVER_LIKERESOURCE_H
