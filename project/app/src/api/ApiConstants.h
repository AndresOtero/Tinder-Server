//
// Created by jonathan on 26/04/16.
//

#ifndef TINDER_SERVER_APICONSTANTS_H_H
#define TINDER_SERVER_APICONSTANTS_H_H

#include <string>
using namespace std;

const string API_STATUS_CODE_PARAM="status";
const string API_RESPONSE_PARAM ="reponse";

const int  API_STATUS_CODE_DONE=200;
const int  API_STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED=101;
const int  API_STATUS_USER_ALREADY_EXIST=102;

//SECURITY

const string SECURITY_TOKEN_PARAM="token";
const string SECURITY_TOKEN_HEADER="SECURITY-TOKEN";

#endif //TINDER_SERVER_APICONSTANTS_H_H
