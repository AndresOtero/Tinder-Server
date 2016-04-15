#ifndef simpleLogger_h__
#define simpleLogger_h__

#define BOOST_LOG_DYN_LINK 1 // necessary when linking the boost_log library dynamically

#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

/**
 * File where to store logs
*/
#define LOGFILE "logfile.log"

/**
 * Default Severety level
 */
#define SEVERITY_THRESHOLD logging::trivial::debug

// register a global logger
BOOST_LOG_GLOBAL_LOGGER(logger, boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>)

/**
 * Helper macro, don't use it
*/
#define CUSTOM_LOG(severity) BOOST_LOG_SEV(logger::get(),boost::log::trivial::severity)

// ===== log macros =====
/**
 * Log message with TRACE level
 * @param message the message to log
*/
#define LOG_TRACE   CUSTOM_LOG(trace)
/**
 * Log message with DEBUGlevel
 * @param message the message to log
*/
#define LOG_DEBUG   CUSTOM_LOG(debug)
/**
 * Log message with INFO level
 * @param message the message to log
*/
#define LOG_INFO    CUSTOM_LOG(info)
/**
 * Log message with WARNING level
 * @param message the message to log
*/
#define LOG_WARNING CUSTOM_LOG(warning)
/**
 * Log message with ERRORlevel
 * @param message the message to log
*/
#define LOG_ERROR   CUSTOM_LOG(error)
/**
 * Log message with FATAL level
 * @param message the message to log
*/
#define LOG_FATAL   CUSTOM_LOG(fatal)

#endif
