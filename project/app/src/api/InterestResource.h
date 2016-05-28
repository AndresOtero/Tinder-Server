//
// Created by jonathan on 27/04/16.
//

#ifndef TINDER_SERVER_INTERESTRESOURCE_H
#define TINDER_SERVER_INTERESTRESOURCE_H

#include <ProfileServices.h>
#include "dispatcher/ApiDispatcher.h"
#include "dispatcher/RestResource.h"
#include "services/profile/ProfileServices.h"
class InterestResource: public RestResource {

private:
    void addInterest(WebContext & wc);
    void searchInterests(WebContext & wc);
    ProfileServices & profileServices;
public:

    InterestResource(ProfileServices &profileService);

    void setup(ApiDispatcher & dispatcher);

};


#endif //TINDER_SERVER_INTERESTRESOURCE_H
