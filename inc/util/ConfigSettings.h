/*
 * ConfigSettings.h
 *
 *  Created on: Jul 14, 2016
 *      Author: developer
 */

#ifndef INC_CONFIGSETTINGS_H_
#define INC_CONFIGSETTINGS_H_

#include <iomanip>
#include <iostream>
#include <fstream>

#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include "SaveModeEnum.h"

using namespace std;

namespace Mitrais
{
	namespace util
	{
		class ConfigSettings
		{
		private:
			friend class boost::serialization::access;
			friend ostream& operator<<(ostream &os, const ConfigSettings &cs);


			template<class Archive>
			void serialize(Archive &ar, const unsigned int )
			{
				ar  & BOOST_SERIALIZATION_NVP(connectionString)
					& BOOST_SERIALIZATION_NVP(logFileName)
					& BOOST_SERIALIZATION_NVP(crawlingDeepness)
					& BOOST_SERIALIZATION_NVP(saveTarget)
					& BOOST_SERIALIZATION_NVP(pathToLocalDir);
			}
		public:
			/**
			 * Default constructor
			 */
			ConfigSettings(){}

			/**
			 * Constructor for initializing value of props
			 */
			ConfigSettings(const string &_cstring,
					const string &_lname,
					const int _crdeep,
					const SaveModeEnum &_svtarg,
					const string &_pathloc) :
			connectionString(_cstring),
			logFileName(_lname),
			crawlingDeepness(_crdeep),
			saveTarget(_svtarg),
			pathToLocalDir(_pathloc)
			{}

			/**
			 * valid connection string as string
			 */
			string connectionString;

			/**
			 * preferred log file name as string
			 */
			string logFileName;

			/**
			 * deepness of the crawling as int
			 */
			int crawlingDeepness;

			/**
			 * saving mode of the app as enum
			 */
			SaveModeEnum saveTarget;

			/**
			 * path of local save dir as string
			 */
			string pathToLocalDir;
		};

		/**
		 * inline definition of operator friend function
		 */
		inline ostream& operator<<(ostream &os, const ConfigSettings &cs)
		{
			return os << "Connection String: " << cs.connectionString <<
					"\n Log File Name: " << cs.logFileName <<
					"\n Crawling Deepness: " << cs.crawlingDeepness <<
					"\n Save To File? " << cs.saveTarget <<
					"\n Path to Local dir: " << cs.pathToLocalDir;
		}
	} /* namespace util */
} /* namespace Mitrais */



#endif /* INC_CONFIGSETTINGS_H_ */
