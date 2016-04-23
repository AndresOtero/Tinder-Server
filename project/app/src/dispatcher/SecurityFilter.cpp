//
// Created by jonathan on 23/04/16.
//

#include <JsonWebToken.h>
#include "SecurityFilter.h"

SecurityFilter::~SecurityFilter() { };

bool SecurityFilter::doFilter(WebContext & context) {
    const string token = context.getRequest().getHeader("SECURITY-TOKEN");
    if(token.size() == 0) {
        context.getResponse().setStatus(STATUS_401_UNAUTHORIZED);
        return false;
    }
    JsonWebToken tokenizr;
    Json::Value values;
    if(tokenizr.getUsernameFromToken(token, values)) {
        return true;
    }
    return false;
}

SecurityFilter::SecurityFilter(AuthenticationService & service) : service(service) { }