
#ifndef APP_SRC_WEBSERVER_RESTREQUEST_H_
#define APP_SRC_WEBSERVER_RESTREQUEST_H_
#include <string>
#include <map>
#include "mongoose/mongoose.h"
using namespace std;
static const string METHOD_TOKEN = " ";
static const string URI_TOKEN = " ";

static const string HEADER_NAME_TOKEN = ":";


/**
 * @class RequestRequest
 * This class dispatches requests to their correct handler
 *
 * @author jtierno
 *
 */
class RestRequest {
private:
	/**
	 * Rquested uri
	 */
	string uri;
	/**
	 * Mongoose message data
	 */
	http_message * message;

	/**
	 * content to render
	 */
	string content;

	/**
	 * Request Headers
	 */
	map<string, string> headers;
	/**
	 * Parse request headers
	 */
	void parseHeaders();

public:
	/**
	 * Constructor with web information
	 * @param web message information
	 */
	RestRequest(http_message * message);
	virtual ~RestRequest();
	/**
	 * Getter for requested uri
	 * @return uri
	 */
	string getUri();

	/**
	 * Getter for header in request
	 * @param name header's name
	 * @return header content if exists, else empty string
	 */
	string getHeader(string name);


	/**
	 * Enum with HTTP METHODS
	 */
	enum Method {
		GET /** GET */
		,PUT /** PUST */
		,POST /** POST */
		,DELETE /** DELETE */
		,UNKNOWN /** UNKNOWN (only helper)*/};

	/**
	 * Get string description
	 * @return string description
	 */
	string toString();

	/**
	 * Get Requested Method
	 * @return a method
	 */
	Method getMethod();

	/**
	 * Get Content
	 * @return a string with content
	 */
	string getContent();
	static string getDescription(RestRequest::Method);
};

#endif /* APP_SRC_WEBSERVER_RESTREQUEST_H_ */
