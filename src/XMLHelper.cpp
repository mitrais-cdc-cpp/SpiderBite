/*
 * XMLHelper.cpp
 *
 *  Created on: Jul 15, 2016
 *      Author: developer
 */

#include "../inc/XMLHelper.h"

namespace Mitrais
{
	namespace util
	{
		/**
		 * Default constructor
		 */
		XMLHelper::XMLHelper()
		{}

		/**
		 * Default destructor
		 */
		XMLHelper::~XMLHelper()
		{}

		/**
		 * Save the configuration to some filename
		 */
		void XMLHelper::save_schedule(const ConfigSettings &s, const char * filename)
		{
			// make an archive
			std::ofstream ofs(filename);
			assert(ofs.good());
			boost::archive::xml_oarchive oa(ofs);
			oa << BOOST_SERIALIZATION_NVP(s);
		}

		/**
		 * Load the file and assign the props value
		 */
		void XMLHelper::restore_schedule(ConfigSettings &s, const char * filename)
		{
			// open the archive
			std::ifstream ifs(filename);
			assert(ifs.good());
			boost::archive::xml_iarchive ia(ifs);

			// restore the setting from the archive
			ia >> BOOST_SERIALIZATION_NVP(s);
		}
	}
}

