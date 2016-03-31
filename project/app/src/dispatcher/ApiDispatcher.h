/*
 * ApiDispatcher.h
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#ifndef SRC_DISPATCHER_APIDISPATCHER_H_
#define SRC_DISPATCHER_APIDISPATCHER_H_


#include <string>
#include <functional>
#include "dispatcher/WebContext.h"
using namespace std;

class ApiDispatcher {
private:


public:
	ApiDispatcher();
	virtual ~ApiDispatcher();
	enum methods {GET='g', PUT='p', PUSH='g', DEL='d'};
	void registerEndPoint(methods method, string uri, function<void (WebContext&)> func);
};

#endif /* SRC_DISPATCHER_APIDISPATCHER_H_ */
