/*
 * XMLHelper.h
 *
 *  Created on: Jul 15, 2016
 *      Author: developer
 */

#ifndef INC_XMLHELPER_H_
#define INC_XMLHELPER_H_

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "ConfigSettings.h"

namespace Mitrais
{
	namespace util
	{
		class XMLHelper
		{
			public:
				XMLHelper();
				~XMLHelper();
				void save_schedule(const ConfigSettings &s, const char * filename);
				void restore_schedule(ConfigSettings &s, const char * filename);
		};
	}
}

#endif /* INC_XMLHELPER_H_ */
