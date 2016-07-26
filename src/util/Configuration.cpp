/*
 * Configuration.cpp
 *
 *  Created on: Jul 19, 2016
 *      Author: developer
 */

#include "../../inc/util/Configuration.h"
namespace Mitrais
{
	namespace util
	{
		/**
		 * Default constructor.
		 */
		Configuration::Configuration()
		{
		}

		/**
		 * Default destructor
		 */
		Configuration::~Configuration()
		{
		}

		/**
		 * The xml file for configuration
		 */
		const string Configuration::_fileName = "Config.xml";

		/**
		 * The XMLHelper object
		 */
		XMLHelper Configuration::_helper;

		/**
		 * The configuration setting object
		 */
		ConfigSettings Configuration::_setting;

		/**
		 * Get the configuration setting
		 * The valid configuration setting will be constructed here
		 * @return ConfigSettings oject
		 */
		ConfigSettings Configuration::getSetting()
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
			return _setting;
		}
	}
}
