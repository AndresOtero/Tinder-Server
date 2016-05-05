/*
 * Constants.h
 *
 *  Created on: 9 de abr. de 2016
 *      Author: jonathan
 */

#ifndef APP_SRC_WEBSERVER_CONSTANTS_H_
#define APP_SRC_WEBSERVER_CONSTANTS_H_

#include <string>
using namespace std;
/**
 *
 */
const static string STATUS_200_OK = "200 OK";
const static string STATUS_400_BAD_REQUEST = "400 Bad Request";
const static string STATUS_401_UNAUTHORIZED= "401 Unauthorized";
const static string STATUS_403_FORBIDDEN = "403 Forbidden";
const static string STATUS_405_METHOD_NOT_ALLOWED = "405 Method Not Allowed";
const static string STATUS_500_INTERNAL_SERVER_ERROR = "500 Internal Server Error";
const static string STATUS_501_NOT_IMPLEMENTED = "501 Not Implemented";


const static string CONTENT_TYPE_JSON = "application/json";


#endif /* APP_SRC_WEBSERVER_CONSTANTS_H_ */
