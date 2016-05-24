#ifndef APP_SRC_DISPATCHER_PARSINGCONTENTEXCEPTIONEXCEPTION_H_
#define APP_SRC_DISPATCHER_NOSUCHMETHODHANDLEREXCEPTION_H_

#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;


/**
 * @class ParsingContentException
 *
 * Exception where a json parsing error
 *
 * @author jtierno
 *
 */
class ParsingContentException: public runtime_error {
public:

	ParsingContentException();
	virtual ~ParsingContentException();
};

#endif /* APP_SRC_DISPATCHER_NOSUCHMETHODHANDLEREXCEPTION_H_ */
