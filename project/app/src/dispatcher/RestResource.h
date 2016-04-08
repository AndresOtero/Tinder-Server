/*
 * RestResource.h
 *
 *  Created on: 7 de abr. de 2016
 *      Author: jonathan
 */

#ifndef APP_SRC_DISPATCHER_RESTRESOURCE_H_
#define APP_SRC_DISPATCHER_RESTRESOURCE_H_
#include "ApiDispatcher.h"

class  RestResource {
public:
	RestResource(){};
	virtual ~RestResource() {};
	virtual void setup(ApiDispatcher & dispatcher) = 0;
};

#endif /* APP_SRC_DISPATCHER_RESTRESOURCE_H_ */
