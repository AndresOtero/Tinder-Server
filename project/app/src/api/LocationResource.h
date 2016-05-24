//
// Created by jonathan on 23/05/16.
//

#ifndef TINDER_SERVER_LOCATIONRESOURCE_H
#define TINDER_SERVER_LOCATIONRESOURCE_H


#include <ProfileServices.h>
#include <RestResource.h>
#include <ChatServices.h>

class LocationResource: public RestResource {
private:
    ProfileServices & service;
public:
    LocationResource(ProfileServices  &service);
    virtual ~LocationResource();
    void setup(ApiDispatcher & dispatcher);
    void updateLocation(WebContext & wc);
};


#endif //TINDER_SERVER_LOCATIONRESOURCE_H
