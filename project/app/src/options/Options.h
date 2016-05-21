//
// Created by matias on 5/19/16.
//

#ifndef TINDER_SERVER_OPTIONS_H
#define TINDER_SERVER_OPTIONS_H

#include <string>
using namespace std;

/**
 * @class Options
 *
 * Structure containing all the information read from the configuration file
 *
 * @author MLuraschi.
 */
class Options {
public:
	/**
	 * Default constructor.
	 *
	 * @param LogLevel level for the logger.
	 * @param SharedServerURL URL of the shared server to used.
	 * @param DbLocation Location of the local DB to be used.
	 */
	Options(string LogLevel, string SharedServerURL, string DbLocation);
	virtual ~Options();

	/**
	 * Returns a string with the log level.
	 */
	string getLogLevel();

	/**
	 * Return a string with the URL of the shared server.
	 */
	string getSharedServerURL();

	/**
	 * Return the location of the local DB to use.
	 */
	string getDbLocation();

private:
	string LogLevel;
	string SharedServerURL;
	string DbLocation;
};


#endif //TINDER_SERVER_OPTIONS_H
