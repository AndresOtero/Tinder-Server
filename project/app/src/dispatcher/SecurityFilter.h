//
// Created by jonathan on 23/04/16.
//

#ifndef TINDER_SERVER_SECURITYFILTER_H
#define TINDER_SERVER_SECURITYFILTER_H

#include <AuthenticationService.h>
#include "Filter.h"

class SecurityFilter: public Filter {
private:
    AuthenticationService & service;
protected:
    bool doFilter(WebContext & context);

public:
    SecurityFilter(AuthenticationService & service);
    virtual ~SecurityFilter();
};


#endif //TINDER_SERVER_SECURITYFILTER_H
