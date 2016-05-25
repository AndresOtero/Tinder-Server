//
// Created by jonathan on 23/04/16.
//

#ifndef TINDER_SERVER_SECURITYFILTER_H
#define TINDER_SERVER_SECURITYFILTER_H

#include <AuthenticationService.h>
#include <regex>
#include "Filter.h"
#include "string"

#include <unordered_map>
#include <set>
using namespace std;

class SecurityFilter: public Filter {
private:
    AuthenticationService & validator;
    unordered_map<string, set<string>> excludedRegexs;
protected:
    bool doFilter(WebContext & context);

public:
    SecurityFilter(AuthenticationService & validator);

    void excludeRegex(RestRequest::Method method, string regex);

    virtual ~SecurityFilter();

    bool isSecured(RestRequest::Method method, string uri);
};


#endif //TINDER_SERVER_SECURITYFILTER_H
