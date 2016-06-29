#include "../inc/Logger.h"

namespace attrs    = boost::log::attributes;
namespace expr     = boost::log::expressions;
namespace logging  = boost::log;
namespace sinks    = boost::log::sinks;
namespace keywords = boost::log::keywords;

//Defines a global logger initialization routine
BOOST_LOG_GLOBAL_LOGGER_INIT(spiderbite_logger, logger_t)
{
    logger_t lg;

    // New attributes that hold filename and line number
    logging::core::get()->add_global_attribute("File", attrs::mutable_constant<std::string>(""));
    logging::core::get()->add_global_attribute("Line", attrs::mutable_constant<int>(0));

    logging::add_common_attributes();

    logging::add_file_log
	(
		keywords::file_name = SYS_LOGFILE,
		keywords::rotation_size = 10*1024*1204,   // rotate files every 10 MiB...
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), //or at midnight
		keywords::format =
		(
			expr::stream
			<< "[" << expr::attr< boost::log::trivial::severity_level >("Severity") << "]: "
			<< expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f ")
			 << '['   << expr::attr<std::string>("File")
			 << ':' << expr::attr<int>("Line") << "] "
			<< expr::smessage
		)
    );

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );

    return lg;
}
