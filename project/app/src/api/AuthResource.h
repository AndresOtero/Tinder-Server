/*
 * AuthResource.h
 *
 *  Created on: 10 de abr. de 2016
 *      Author: jonathan
 */

#ifndef APP_SRC_API_AUTHRESOURCE_H_
#define APP_SRC_API_AUTHRESOURCE_H_

#include "services/authentication/AuthenticationService.h"
#include "dispatcher/WebContext.h"
#include <RestResource.h>


class AuthResource: public RestResource {
private :
	AuthenticationService *service;
public:
	AuthResource(AuthenticationService * service);
	void setup(ApiDispatcher & dispatcher);
	void authenticate(WebContext & wc);
	virtual ~AuthResource();
};

#endif /* APP_SRC_API_AUTHRESOURCE_H_ */
