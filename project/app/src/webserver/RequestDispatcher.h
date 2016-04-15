
#ifndef SRC_WEBSERVER_REQUESTDISPATCHER_H_
#define SRC_WEBSERVER_REQUESTDISPATCHER_H_


#include <string>
#include <functional>
#include "dispatcher/WebContext.h"
using namespace std;


/**
 * @class RequestDispatcher
 * This class dispatches requests to their correct handler
 *
 * @author jtierno
 *
 */
class RequestDispatcher {

public:

	/**
	 * Handles a request dispatching to the correct handler
	 * @param request RestRequest
	 * @param response RestResponse where tp build the response
	 */

	virtual void handle(RestRequest & request, RestResponse & response) = 0;
	virtual ~RequestDispatcher(){};
};

#endif /* SRC_WEBSERVER_REQUESTDISPATCHER_H_ */
