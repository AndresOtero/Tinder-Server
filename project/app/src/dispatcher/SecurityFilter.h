//
// Created by jonathan on 23/04/16.
//

#ifndef TINDER_SERVER_SECURITYFILTER_H
#define TINDER_SERVER_SECURITYFILTER_H

#include <AuthenticationService.h>
#include <regex>
#include "Filter.h"
#include "string"

using namespace std;

class SecurityFilter: public Filter {
private:
    AuthenticationService & service;
    list<regex> excludedRegexs;
protected:
    bool doFilter(WebContext & context);

public:
    SecurityFilter(AuthenticationService & service);

    void excludeRegex(string regex);

    virtual ~SecurityFilter();

    bool isSecured(string uri);
};


#endif //TINDER_SERVER_SECURITYFILTER_H
