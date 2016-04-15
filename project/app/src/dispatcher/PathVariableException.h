
#ifndef APP_SRC_DISPATCHER_PATHVARIABLEEXCEPTION_H_
#define APP_SRC_DISPATCHER_PATHVARIABLEEXCEPTION_H_

#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

/**
 * @class PathVariableException
 *
 * Error reading a path variable in uri
 *
 * @author jtierno
 *
 */

class PathVariableException: public runtime_error  {
public:
	/**
	 * Constructor with error description
	 * @param error error descrpition
	 */
	PathVariableException(string error);
	virtual ~PathVariableException();
};

#endif /* APP_SRC_DISPATCHER_PATHVARIABLEEXCEPTION_H_ */
