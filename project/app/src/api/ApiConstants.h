//
// Created by jonathan on 26/04/16.
//

#ifndef TINDER_SERVER_APICONSTANTS_H_H
#define TINDER_SERVER_APICONSTANTS_H_H

#include <string>
using namespace std;

const string STATUS_CODE_PARAM="statusCode";
const int  STATUS_CODE_DONE=200;
const int STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED=101;

//SECURITY

const string SECURITY_TOKEN_PARAM="token";
const string SECURITY_TOKEN_HEADER="SECURITY-TOKEN";

#endif //TINDER_SERVER_APICONSTANTS_H_H
