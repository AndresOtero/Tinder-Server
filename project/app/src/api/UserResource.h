/*
 * UserResource.h
 *
 *  Created on: 7 de abr. de 2016
 *      Author: jonathan
 */

#ifndef APP_SRC_API_USERRESOURCE_H_
#define APP_SRC_API_USERRESOURCE_H_

#include "dispatcher/RestResource.h"
#include "dispatcher/WebContext.h"

class UserResource: public RestResource {
private:
	void getUser(WebContext &);
	void putUser(WebContext &);
public:
	UserResource();
	void setup(ApiDispatcher & dispatcher);
	virtual ~UserResource();
};

#endif /* APP_SRC_API_USERRESOURCE_H_ */
