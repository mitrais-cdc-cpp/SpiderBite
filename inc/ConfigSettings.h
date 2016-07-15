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
			friend class boost::serialization::access;
			friend std::ostream & operator<<(std::ostream &os, const ConfigSettings &cs);

			string connectionString;	// valid connection string as string
			string logFileName;			// preferred log file name as string
			int crawlingDeepness;		// deepness of the crawling as int
			SaveModeEnum saveTarget;	// saving mode of the app as enum
			string pathToLocalDir;		// path of local save dir as string

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

		};

		BOOST_SERIALIZATION_ASSUME_ABSTRACT(ConfigSettings)

		ostream & operator<<(std::ostream &os, const ConfigSettings &cs)
		{
			return os << '\n' << cs.connectionString << '\n' << cs.logFileName << '\n'
					<< cs.crawlingDeepness << '\n' << cs.saveTarget << '\n' << cs.pathToLocalDir << '\n';
		}
	} /* namespace util */
} /* namespace Mitrais */



#endif /* INC_CONFIGSETTINGS_H_ */
