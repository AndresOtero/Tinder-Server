/*
 * JsonWebToken.h
 *
 *  Created on: Mar 21, 2016
 *      Author: matias
 */

#ifndef SRC_JSONWEBTOKEN_H_
#define SRC_JSONWEBTOKEN_H_

#include <string>
#include "json/json.h"

/**
 * @class JsonWebToken
 *
 * Provides the functionality to create and validate jwt.
 */
class JsonWebToken {
public:
	JsonWebToken();
	virtual ~JsonWebToken();

	/**
	 * Generates a jwt for the given username. It does not check if the username exists.
	 *
	 * @param username to generate the jwt for.
	 */
	std::string generateTokenForUser(std::string username);

	/**
	 * Checks if the jwt received is valid and returns the payload of it if it is.
	 *
	 * @param token to decode and validate.
	 * @param returnPayload the payload of the decoded jwt is stored here.
	 */
	bool getUsernameFromToken(std::string token, Json::Value& returnPayload);

private:
	std::string decodeBase64(std::string encoded);
	std::string generateHeader();
	std::string generatePayload(std::string username);
	std::string encodeBase64(std::string input);
};
#endif /* SRC_JSONWEBTOKEN_H_ */