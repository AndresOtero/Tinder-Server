
#ifndef APP_SRC_API_AUTHRESOURCE_H_
#define APP_SRC_API_AUTHRESOURCE_H_

#include "services/authentication/AuthenticationService.h"
#include "dispatcher/WebContext.h"
#include <RestResource.h>


/**
 * @class AuthResource
 * Authentication Resource, provides authentication capability
 *
 * @author jtierno
 *
 */

class AuthResource: public RestResource {
private :
	/**
	 * Serivice for authentication
	 */
	AuthenticationService *service;
public:
    /**
     * Constructor that sets the AuthenticationService.
     *
     * @param service the AuthenticationService to authenticate
     *
     * @see AuthenticationService
     */
	AuthResource(AuthenticationService * service);

	void setup(ApiDispatcher & dispatcher);

    /**
     * Authenticate an user
     *
     * @param wc WebContext Rest request context
     *
     */
	void authenticate(WebContext & wc);

	virtual ~AuthResource();
};

#endif /* APP_SRC_API_AUTHRESOURCE_H_ */
