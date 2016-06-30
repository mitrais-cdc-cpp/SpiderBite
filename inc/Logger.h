#ifndef SPIDERBITE_INC_TEXTLEXER_H_
#define SPIDERBITE_INC_TEXTLEXER_H_

#include <boost/log/expressions.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/attributes/mutable_constant.hpp>

#define LOG_INFO  BOOST_LOG_SEV(spiderbite_logger::get(), boost::log::trivial::info)     << "[" <<std::string(__FILE__).substr(std::string( __FILE__).find_last_of("/\\")+1) << " : " << BOOST_CURRENT_FUNCTION << " : "<<__LINE__<< "] "
#define LOG_DEBUG BOOST_LOG_SEV(spiderbite_logger::get(), boost::log::trivial::debug)    << "[" <<std::string(__FILE__).substr(std::string( __FILE__).find_last_of("/\\")+1) << " : " << BOOST_CURRENT_FUNCTION << " : "<<__LINE__<< "] "
#define LOG_WARN  BOOST_LOG_SEV(spiderbite_logger::get(), boost::log::trivial::warning)  << "[" <<std::string(__FILE__).substr(std::string( __FILE__).find_last_of("/\\")+1) << " : " << BOOST_CURRENT_FUNCTION << " : "<<__LINE__<< "] "
#define LOG_ERROR BOOST_LOG_SEV(spiderbite_logger::get(), boost::log::trivial::error)    << "[" <<std::string(__FILE__).substr(std::string( __FILE__).find_last_of("/\\")+1) << " : " << BOOST_CURRENT_FUNCTION << " : "<<__LINE__<< "] "
#define LOG_FATAL BOOST_LOG_SEV(spiderbite_logger::get(), boost::log::trivial::fatal)    << "[" <<std::string(__FILE__).substr(std::string( __FILE__).find_last_of("/\\")+1) << " : " << BOOST_CURRENT_FUNCTION << " : "<<__LINE__<< "] "


#define SYS_LOGFILE             "spiderbite_%N.log"

//Narrow-char thread-safe logger.
typedef boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> logger_t;

//declares a global logger with a custom initialization
BOOST_LOG_GLOBAL_LOGGER(spiderbite_logger, logger_t)

#endif /* SPIDERBITE_INC_TEXTLEXER_H_ */
