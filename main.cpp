/*
 * main.cpp
 *
 *  Created on: May 30, 2016
 *      Author: ari
 */

#include <iostream>
#include <boost/archive/tmpdir.hpp>

#include "inc/view/MainUI.h"

using namespace Mitrais::UI;
using namespace Mitrais::util;
using namespace std;

int main(int argc, char* argv[])
{
	// logger example
	LOG_INFO << "Program started";
	MainUI ab;
	ab.activateUI(argc, argv);

//	ThreadHelper helper;
//	helper.executeTaskAsync(3);

//	ConfigSettings settings("a","b",1,SAVE_TO_DB,"e");
//	std::string filename(boost::archive::tmpdir());
//	filename += "/sett.xml";
//
//	XMLHelper helper;
//	helper.save_schedule(settings, filename.c_str());
//
//	ConfigSettings conf;
//	helper.restore_schedule(conf, filename.c_str());
//	cout << conf;

	return 0;
}


