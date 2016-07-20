/*
 * Conifguration.h
 *
 *  Created on: Jul 19, 2016
 *      Author: developer
 */

#ifndef INC_CONFIGURATION_H_
#define INC_CONFIGURATION_H_
#include <cstring>
#include "XMLHelper.h"
#include <boost/filesystem.hpp>

using namespace std;

namespace Mitrais
{
	namespace util
	{
		class Configuration
		{
			public:
				/**
				 * Default constructor
				 */
				Configuration();

				/**
				 * Default destructor
				 */
				~Configuration();

				/**
				 * Get the configuration setting
				 * @return ConfigSettings oject
				 */
				static ConfigSettings getSetting();

			private:
				/**
				 * The xml file for configuration
				 */
				static const string _fileName;

				/**
				 * The XMLHelper object
				 */
				static XMLHelper _helper;

				/**
				 * The configuration setting object
				 */
				static ConfigSettings _setting;
		};
	}
}


#endif /* INC_CONIFGURATION_H_ */
