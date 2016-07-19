/*
 * Configuration.cpp
 *
 *  Created on: Jul 19, 2016
 *      Author: developer
 */

#include "../inc/Configuration.h"
namespace Mitrais
{
	namespace util
	{
		/**
		 * Default constructor.
		 * The valid configuration setting will be constructed here
		 */
		Configuration::Configuration()
		{
			if(boost::filesystem::exists(_fileName.c_str()))
			{
				_helper.loadXML(_setting, _fileName.c_str());
			}
			else
			{
				_setting.connectionString = "";
				_setting.crawlingDeepness = 2;
				_setting.logFileName = "spiderbite";
				_setting.saveTarget = SAVE_TO_FILE;
				_setting.pathToLocalDir = "";
			}
		}

		/**
		 * Default destructor
		 */
		Configuration::~Configuration()
		{
		}

		/**
		 * Get the configuration setting
		 * @return ConfigSettings oject
		 */
		ConfigSettings Configuration::getSetting()
		{
			return _setting;
		}
	}
}
