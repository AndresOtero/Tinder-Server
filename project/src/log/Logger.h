/*
 * Logger.h
 *
 *  Created on: 20 de mar. de 2016
 *      Author: jonathan
 */

#ifndef SRC_LOG_LOGGER_H_
#define SRC_LOG_LOGGER_H_

#include <string>
using namespace std;

class Logger {
public:
	Logger();
	virtual ~Logger();
	void info(string message);
	void debug(string message);
	void error(string message);
};

#endif /* SRC_LOG_LOGGER_H_ */
