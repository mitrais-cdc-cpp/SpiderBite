/*
 * main.cpp
 *
 *  Created on: May 30, 2016
 *      Author: ari
 */

#include <iostream>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "inc/ui/MainUI.h"
#include "inc/ConfigSettings.h"

using namespace Mitrais::UI;
using namespace Mitrais::util;
using namespace std;


void save_schedule(const ConfigSettings &s, const char * filename){
    // make an archive
    std::ofstream ofs(filename);
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(s);
}

void restore_schedule(ConfigSettings &s, const char * filename)
{
    // open the archive
    std::ifstream ifs(filename);
    assert(ifs.good());
    boost::archive::xml_iarchive ia(ifs);

    // restore the schedule from the archive
    ia >> BOOST_SERIALIZATION_NVP(s);
}

int main(int argc, char* argv[])
{
	// logger example
	LOG_INFO << "Program started";
//	MainUI ab;
//	ab.activateUI(argc, argv);

	ConfigSettings settings("a","b",1,SAVE_TO_DB,"e");
	std::string filename(boost::archive::tmpdir());
	filename += "/sett.xml";

	// save the schedule
	save_schedule(settings, filename.c_str());

	return 0;
}


