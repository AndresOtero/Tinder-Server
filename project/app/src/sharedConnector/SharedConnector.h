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
#include "../json/json/json.h"


class SharedConnector {
public:
	SharedConnector(std::string serverBaseURL);
	virtual ~SharedConnector();
	bool testConnection();
	bool getJsonFromURL(std::string endpoint, Json::Value& jsonData);
	bool putDataToURL(std::string endpoint, std::string data);
	bool postDataToURL(std::string endpoint, std::string data);
	bool deleteToURL(std::string endpoint);
	std::string serverBaseURL;


private:
	bool returnedError(CURLcode res);

};

#endif /* SRC_SHAREDCONNECTOR_H_ */
