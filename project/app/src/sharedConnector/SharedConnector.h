/*
 * SharedConnector.h
 *
 *  Created on: Apr 1, 2016
 *      Author: matias
 */

#ifndef SRC_SHAREDCONNECTOR_H_
#define SRC_SHAREDCONNECTOR_H_

#include <string>
#include <curl/curl.h>
#include "json/json/json.h"


class SharedConnector {
public:
	SharedConnector(std::string serverBaseURL);
	virtual ~SharedConnector();
	bool testConnection();
	bool getAllUsers(Json::Value& usersData);
	bool getUserByID(int id, Json::Value& userData);

private:
	std::string serverBaseURL;
	CURL *curl;
	CURLcode res;
	bool returnedError();
	bool getJsonFromURL(std::string url, Json::Value& jsonSata);

};

#endif /* SRC_SHAREDCONNECTOR_H_ */
