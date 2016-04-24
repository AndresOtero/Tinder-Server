//
// Created by jonathan on 23/04/16.
//

#include <JsonWebToken.h>
#include "SecurityFilter.h"

SecurityFilter::~SecurityFilter() { };

bool SecurityFilter::doFilter(WebContext &context) {
    if (isSecured(context.getRequest().getUri())) {
        const string token = context.getRequest().getHeader("SECURITY-TOKEN");
        if (token.size() == 0) {
            context.getResponse().setStatus(STATUS_401_UNAUTHORIZED);
            return false;
        }
        JsonWebToken tokenizr;
        Json::Value values;
        if (tokenizr.getUsernameFromToken(token, values)) {
            return true;
        }
        return false;
    }
    return true;
}

SecurityFilter::SecurityFilter(AuthenticationService &service) : service(service) { }

void SecurityFilter::excludeRegex(string regexpression) {
    this->excludedRegexs.push_back(regex(regexpression));
}

bool SecurityFilter::isSecured(string uri) {
    for (std::list<regex>::iterator it = excludedRegexs.begin(); it != excludedRegexs.end(); ++it) {
        if (regex_match(uri, *it)) {
            return false;
        }
    }
    return true;
}

