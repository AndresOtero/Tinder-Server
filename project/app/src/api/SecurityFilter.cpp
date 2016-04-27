//
// Created by jonathan on 23/04/16.
//

#include <JsonWebToken.h>
#include "SecurityFilter.h"
#include "ApiConstants.h"
SecurityFilter::~SecurityFilter() { };

bool SecurityFilter::doFilter(WebContext &context) {
    //context.setUserid("anonymous");
    if (isSecured(context.getRequest().getUri())) {
        const string token = context.getRequest().getHeader(SECURITY_TOKEN_HEADER);
        if (token.size() == 0) {
            context.getResponse().setStatus(STATUS_401_UNAUTHORIZED);
            return false;
        }
        JsonWebToken tokenizr;
        Json::Value values;
        if (tokenizr.getUsernameFromToken(token, values)) {
            //context.setUsername(values.get("user", "Invalid Token").asString());
            //TODO OBTENER EL ID DEL SERVICIO DE AUTENTICACION Y PONERLO EN EL CONTAINER.
            context.setUserid(0);
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

