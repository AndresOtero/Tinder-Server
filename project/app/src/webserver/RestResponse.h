#ifndef APP_SRC_WEBSERVER_RESTRESPONSE_H_
#define APP_SRC_WEBSERVER_RESTRESPONSE_H_

#include <string>
#include "mongoose/mongoose.h"
#include "Constants.h"
using namespace std;



/**
 * @class RestResponse
 * Builds a web response
 *
 * @author jtierno
 *
 */
class RestResponse {
private:
	/**
	 * Status that to be will answered
	 */
	string status;
	/**
	 * Content that to be will answered
	 */
	string body;
	/**
	 * Content type to be will answered
	 */

	string contentType;
public:

	RestResponse();
	virtual ~RestResponse();

	/**
	 * Set status
	 * @param status The status
	 */
	void setStatus(string status);
	/**
	 * Set Content
	 * @param body The content
	 */

	void setContent(string body);

	/**
	 * Set content type
	 * @param contentType the content type
	 */

	void setContentType(string contentyType);
	/**
	 * Get status
	 * @return the status
	 */

	string getStatus();

	/**
	 * Writes the answer
	 * @param nc connection where render the answer
	 */

	void render (mg_connection *nc);
};

#endif /* APP_SRC_WEBSERVER_RESTRESPONSE_H_ */
