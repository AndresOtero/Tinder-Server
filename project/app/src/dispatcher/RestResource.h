
#ifndef APP_SRC_DISPATCHER_RESTRESOURCE_H_
#define APP_SRC_DISPATCHER_RESTRESOURCE_H_
#include "ApiDispatcher.h"
#include "json/json.h"
/**
 * @class RestResource
 *
 *
 * @author jtierno

 * Generic RestResource that represents a handler for a set of requests on an REST API
 */

class  RestResource {
public:
	RestResource(){};
	virtual ~RestResource() {};
    /**
     * Configures Requests handled by this RestResource.
     *
     * @param dispatcher ApiDispatcher where register hadlers
     */
	virtual void setup(ApiDispatcher & dispatcher) = 0;
	static void readJson(WebContext &wc, Json::Value &);
	static void writeJsonResponse(WebContext &wc, Json::Value &value, int apiStatus);
	static void writeJsonResponse(WebContext &wc, Json::Value &value);
    static void writeJsonResponse(WebContext &wc);
    static void writeJsonResponse(WebContext &wc, int apiStatus);
};




#endif /* APP_SRC_DISPATCHER_RESTRESOURCE_H_ */
