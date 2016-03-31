#ifndef simpleLogger_h__
#define simpleLogger_h__

#define BOOST_LOG_DYN_LINK 1 // necessary when linking the boost_log library dynamically

#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

// the logs are also written to LOGFILE
#define LOGFILE "logfile.log"

// just log messages with severity >= SEVERITY_THRESHOLD are written
#define SEVERITY_THRESHOLD logging::trivial::info

// register a global logger
BOOST_LOG_GLOBAL_LOGGER(logger, boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>)

// just a helper macro used by the macros below - don't use it in your code
#define CUSTOM_LOG(severity) BOOST_LOG_SEV(logger::get(),boost::log::trivial::severity)

// ===== log macros =====
#define LOG_TRACE   CUSTOM_LOG(trace)
#define LOG_DEBUG   CUSTOM_LOG(debug)
#define LOG_INFO    CUSTOM_LOG(info)
#define LOG_WARNING CUSTOM_LOG(warning)
#define LOG_ERROR   CUSTOM_LOG(error)
#define LOG_FATAL   CUSTOM_LOG(fatal)

#endif
