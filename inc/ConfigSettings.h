/*
 * ConfigSettings.h
 *
 *  Created on: Jul 14, 2016
 *      Author: developer
 */

#ifndef INC_CONFIGSETTINGS_H_
#define INC_CONFIGSETTINGS_H_

#include<iostream>
#include<string>

#include "SaveModeEnum.h"

using namespace std;

namespace Mitrais
{
	namespace util
	{
		/**
		 * Structure to hold spiderbite configuration settings
		 */
		struct UrlTarget
		{
			string connectionString;	// valid connection string as string
			string logFileName;			// preferred log file name as string
			int crawlingDeepness;		// deepness of the crawling as int
			SaveModeEnum saveTarget;	// saving mode of the app as enum
			string pathToLocalDir;		// path of local save dir as string
		};

	} /* namespace util */
} /* namespace Mitrais */



#endif /* INC_CONFIGSETTINGS_H_ */
