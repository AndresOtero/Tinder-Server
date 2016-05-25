//
// Created by jonathan on 23/04/16.
//

#include <JsonWebToken.h>
#include "SecurityFilter.h"
SecurityFilter::~SecurityFilter() {

};

bool SecurityFilter::doFilter(WebContext &context) {
    //context.setUserid("anonymous");
    if (isSecured(context.getRequest().getMethod(), context.getRequest().getUri())) {
        const string token = context.getRequest().getHeader(SECURITY_TOKEN_HEADER);
        if (token.size() == 0) {
            context.getResponse().setStatus(STATUS_401_UNAUTHORIZED);
            return false;
        }
        JsonWebToken tokenizr;
        Json::Value values;
        if (tokenizr.getUsernameFromToken(token, values)) {

            string user = values.get("name", "User is Empty").asString();
            if (this->validator.isValid(user)) {
                context.setUserid(user);
                return true;
            }
        }

        context.getResponse().setStatus(STATUS_401_UNAUTHORIZED);
        return false;
    }
    return true;
}

SecurityFilter::SecurityFilter(UserValidator &validator) : validator(validator) { }

void SecurityFilter::excludeRegex(RestRequest::Method method, string regularExp) {
    unordered_map<string , set<string>>::const_iterator got = this->excludedRegexs.find(RestRequest::getDescription(method));
    if ( got == this->excludedRegexs.end() ) {
        set<string> newSet;
        newSet.insert(regularExp);
        this->excludedRegexs[RestRequest::getDescription(method)] = newSet;
    } else {
        set<string> valores = got->second;
        valores.insert(regularExp);
        this->excludedRegexs[RestRequest::getDescription(method)] = valores;
    }
}

bool SecurityFilter::isSecured(RestRequest::Method method, string uri) {
    unordered_map<string , set<string>>::const_iterator got = this->excludedRegexs.find(RestRequest::getDescription(method));
    if ( got == this->excludedRegexs.end() ) {
        return true;
    }
    for (std::set<string>::iterator it = got->second.begin(); it != got->second.end(); ++it) {
        regex reg = regex(*it);
        if (regex_match(uri, reg)) {
            return false;
        }
    }
    return true;
}

