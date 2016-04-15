
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
	string uri;
	http_message * message;
	string content;
	string extractUri(http_message* hm);


public:
	RestRequest(http_message *);
	virtual ~RestRequest();
	string getUri();
	enum Method {GET, PUT, POST, DELETE, UNKNOWN};
	string toString();
	Method getMethod();
	string getContent();
	static string getDescription(RestRequest::Method);
};

#endif /* APP_SRC_WEBSERVER_RESTREQUEST_H_ */
