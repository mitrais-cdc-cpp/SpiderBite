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
				ar  & BOOST_SERIALIZATION_NVP(dbHost)
					& BOOST_SERIALIZATION_NVP(dbPort)
					& BOOST_SERIALIZATION_NVP(dbName)
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
			 // TODO:
			ConfigSettings(
					const string &_dbhost,
					const int &_dbport,
					const string &_dbname,
					const string &_lname,
					const int _crdeep,
					const SaveModeEnum &_svtarg,
					const string &_pathloc) :
			dbHost(_dbhost),
			dbPort(_dbport),
			dbName(_dbname),
			logFileName(_lname),
			crawlingDeepness(_crdeep),
			saveTarget(_svtarg),
			pathToLocalDir(_pathloc)
			{}

			/**
			 * valid database host as string
			 */
			string dbHost;

			/**
			 * TODO : should be integer
			 * valid database host as string
			 */
			int dbPort;

			/**
			 * valid database name as string
			 */
			string dbName;

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
			return os << "Database Host: " << cs.dbHost <<
					"\n Database Port: " << cs.dbPort <<
					"\n Database Name: " << cs.dbName <<
					"\n Log File Name: " << cs.logFileName <<
					"\n Crawling Deepness: " << cs.crawlingDeepness <<
					"\n Save To File? " << cs.saveTarget <<
					"\n Path to Local dir: " << cs.pathToLocalDir;
		}
	} /* namespace util */
} /* namespace Mitrais */



#endif /* INC_CONFIGSETTINGS_H_ */
