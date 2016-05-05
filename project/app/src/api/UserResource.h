#ifndef APP_SRC_API_USERRESOURCE_H_
#define APP_SRC_API_USERRESOURCE_H_

#include <ProfileServices.h>
#include "dispatcher/RestResource.h"
#include "dispatcher/WebContext.h"

/**
 * @class UserResource
 * Provides user methods
 *
 * @author jtierno
 *
 */

class UserResource: public RestResource {
private:
    /**
     * Obtain an user.
     *
     * @param wc WebContext with RestRequest context.
     *
     * @see AuthenticationService
     */
	void getUser(WebContext & wc);
	void saveUser(WebContext &wc);
	ProfileServices & service;
public:
	/**
	 * Constructor with dependencies
	 * @param service ProfileServices with business logic.
	 */
	UserResource(ProfileServices & service);
	void setup(ApiDispatcher & dispatcher);
	virtual ~UserResource();
};

#endif /* APP_SRC_API_USERRESOURCE_H_ */
