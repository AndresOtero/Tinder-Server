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
using namespace std;
/**
 * @class SharedConnector
 *
 * Provides methods to interact with an API Rest.
 */
class SharedConnector {
public:

	/**
	 * Default constructor.
	 *
	 * @param serverBaseURL base URL of the server where the API rest is.
	 */
	SharedConnector(std::string serverBaseURL);
	virtual ~SharedConnector();

	/**
	 * Method that tries to reach the given base URL. It returns true or false whether the served is reachable or not.
	 */
	bool testConnection();

	/**
	 * Using the verb Get it hits the endpoint received and parses the respond as Json.
	 *
	 * @param endpoint endpoint to hit. It is going to be appended to the baseURL stored.
	 * @param jsonData the parsed response is going to be stored here.
	 */
	void getJsonFromURL(std::string endpoint, Json::Value &jsonData);

	/**
	 * Using the verb Put it send data to the endpoint received and stores the response.
	 *
	 * @param endpoint to hit with the verb. It is appended to the base URL.
	 * @param data to send to the endpoint.
	 * @param response the response of the request is stored there.
	 */
	void putDataToURL(std::string endpoint, std::string data, Json::Value &response);

	/**
	 * Using the verb Post it send data to the endpoint received and stores the response. It returns true or false if
	 * the call wass successful.
	 *
	 * @param endpoint to hit with the verb. It is appended to the base URL.
	 * @param data to send to the endpoint.
	 * @param response the response of the request is stored there.
	 */
	void postDataToURL(std::string endpoint, std::string data, Json::Value &expectedResponse);

	/**
	 * Using the verb Post it send data to the endpoint received and stores the response as a Json. It returns true or false if
	 * the call wass successful.
	 *
	 * @param endpoint to hit with the verb. It is appended to the base URL.
	 * @param data to send to the endpoint.
	 * @param response the response of the request is stored there.
	 */
	void postDataToURL(std::string endpoint, std::string data, std::string &response);

	/**
	 * It send the verb DELETE to the given endpoint in the base url.
	 *
	 * @param endpoint to append to the base url.
	 */
	void deleteToURL(std::string endpoint);
	std::string serverBaseURL;


private:
	string returnedError(CURLcode res);

};

#endif /* SRC_SHAREDCONNECTOR_H_ */
