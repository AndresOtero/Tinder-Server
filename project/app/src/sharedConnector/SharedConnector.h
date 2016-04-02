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

class SharedConnector {
public:
	SharedConnector(std::string serverBaseURL);
	virtual ~SharedConnector();
	bool testConnection();

private:
	std::string serverBaseURL;
	CURL *curl;
	CURLcode res;

};

#endif /* SRC_SHAREDCONNECTOR_H_ */
