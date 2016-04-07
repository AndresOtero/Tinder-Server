#include "JsonWebToken.h"
#include "json/json/json.h"	
#include <cryptopp/base64.h>

using namespace CryptoPP;

JsonWebToken::JsonWebToken() {}
JsonWebToken::~JsonWebToken() {}

std::string JsonWebToken::generateTokenForUser(std::string username) {
	std::string header = this->encodeBase64(this->generateHeader());
	std::string payload = this->encodeBase64(this->generatePayload(username));
	std::string signature = header + payload;
	return header + "." + payload + "." + signature;
}

bool JsonWebToken::getUsernameFromToken(std::string token, std::string& username) {
	int firstDot = token.find_first_of(".");
	int lastDot = token.find_last_of(".");
	std::string header = token.substr(0,firstDot);
	std::string payload = token.substr(firstDot+1, lastDot-(firstDot + 1));
	std::string signature = token.substr(lastDot+1, token.length()-(lastDot + 1));
	if (header + payload != signature) return false; //token invalido
	std::string decodedPayload = this->decodeBase64(payload);
	Json::Value parsedFromString;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(decodedPayload, parsedFromString);
	if (!parsingSuccessful) return false; //error en el json
	username = parsedFromString.get("name", "ERROR").asString();
	return true;
}

std::string JsonWebToken::decodeBase64(std::string encoded) {
	std::string decoded;
	   
	Base64Decoder decoder;
	 
	decoder.Attach( new StringSink( decoded ) );
	decoder.Put( (byte*)encoded.data(), encoded.size() );
	decoder.MessageEnd();
	return decoded;
}

std::string JsonWebToken::generateHeader() {
	Json::Value json;
	json["typ"] = "JWT";
	json["alg"] = "HS256";
	Json::FastWriter writer;
	return writer.write(json);
}

std::string JsonWebToken::generatePayload(std::string username) {
	Json::Value json;
	json["iss"] = "Tinder2-Shared";
	json["name"] = username;
	Json::FastWriter writer;
	return writer.write(json);
}

std::string JsonWebToken::encodeBase64(std::string input) {
	std::string encoded;
	StringSource ss(input, true, new Base64Encoder(new StringSink(encoded), false));
	return encoded;
}