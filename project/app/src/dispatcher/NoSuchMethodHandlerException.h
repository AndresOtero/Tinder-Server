#ifndef APP_SRC_DISPATCHER_NOSUCHMETHODHANDLEREXCEPTION_H_
#define APP_SRC_DISPATCHER_NOSUCHMETHODHANDLEREXCEPTION_H_

#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;


/**
 * @class NoSuchMethodHandlerException
 *
 * Exception where a uri  has not been handled
 *
 * @author jtierno
 *
 */
class NoSuchMethodHandlerException: public runtime_error {
public:

	/**
	 * Constructor with uri
	 * @param uri uri that is not found him handler
	 */
	NoSuchMethodHandlerException(string uri);
	virtual ~NoSuchMethodHandlerException();
};

#endif /* APP_SRC_DISPATCHER_NOSUCHMETHODHANDLEREXCEPTION_H_ */
