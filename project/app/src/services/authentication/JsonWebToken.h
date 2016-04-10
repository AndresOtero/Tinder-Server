/*
 * JsonWebToken.h
 *
 *  Created on: Mar 21, 2016
 *      Author: matias
 */

#ifndef SRC_JSONWEBTOKEN_H_
#define SRC_JSONWEBTOKEN_H_

#include <string>
#include "../../json/json/json.h"

class JsonWebToken {
public:
	JsonWebToken();
	virtual ~JsonWebToken();
	std::string generateTokenForUser(std::string username);
	bool getUsernameFromToken(std::string token, Json::Value& returnPayload);

private:
	std::string decodeBase64(std::string encoded);
	std::string generateHeader();
	std::string generatePayload(std::string username);
	std::string encodeBase64(std::string input);
};
#endif /* SRC_JSONWEBTOKEN_H_ */