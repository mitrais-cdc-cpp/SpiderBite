/*
 * main.cpp
 *
 *  Created on: May 30, 2016
 *      Author: ari
 */

#include <iostream>
#include "inc/ui/MainUI.h"
#include "inc/WebSaver.h"

using namespace Mitrais::UI;
using namespace Mitrais::util;
using namespace std;

int main(int argc, char* argv[])
{
//	MainUI ab;
//	ab.activateUI(argc, argv);

//	util::WebSaver save("https://www.dropbox.com/s/a1t4lwrwxc67o3i/target%20belanja.txt?dl=0");
//	save.saveWebsite();
	std::string url = "http://www.google.com";
	util::WebSaver saver(url);
	saver.saveWebsite();

	return 0;
}


