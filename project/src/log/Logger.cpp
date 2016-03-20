/*
 * Logger.cpp
 *
 *  Created on: 20 de mar. de 2016
 *      Author: jonathan
 */

#include <log/Logger.h>
#include <boost/log/trivial.hpp>

Logger::Logger() {
	// TODO Auto-generated constructor stub

}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

void Logger::info(string message) {
	BOOST_LOG_TRIVIAL(info) << message;
}

void Logger::debug(string message) {
	BOOST_LOG_TRIVIAL(debug) << message;
}

void Logger::error(string message) {
	BOOST_LOG_TRIVIAL(error) << message;
}
