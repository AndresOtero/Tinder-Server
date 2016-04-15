
#ifndef APP_SRC_WEBSERVER_RESTREQUEST_H_
#define APP_SRC_WEBSERVER_RESTREQUEST_H_
#include <string>
#include <map>
#include "mongoose/mongoose.h"
using namespace std;


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
	 * Extracts uri from mongoose message
	 * @return uri
	 */
	string extractUri(http_message* hm);


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
