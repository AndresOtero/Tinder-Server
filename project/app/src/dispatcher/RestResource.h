
#ifndef APP_SRC_DISPATCHER_RESTRESOURCE_H_
#define APP_SRC_DISPATCHER_RESTRESOURCE_H_
#include "ApiDispatcher.h"

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
	static Json::Value readJson(WebContext & wc);
	static void writeJson(WebContext &wc, Json::Value &value);
};

Json::Value RestResource::readJson(WebContext &wc) {
	Json::Reader reader;
	Json::Value parsed;
	bool success = reader.parse(wc.getRequest().getContent(), parsed);
	if(success) {
		return parsed;
	}
	throw "Error reading json";

}

void RestResource::writeJson(WebContext &wc, Json::Value &value) {
	Json::FastWriter writer;
	string content = writer.write(value);
	wc.getResponse().setContent(content);
}


#endif /* APP_SRC_DISPATCHER_RESTRESOURCE_H_ */
