/*
 * main.cpp
 *
 *  Created on: May 30, 2016
 *      Author: ari
 */

#include <iostream>
#include "inc/ui/MainUI.h"

using namespace Mitrais::UI;
using namespace Mitrais::util;
using namespace std;

int main(int argc, char* argv[])
{
	// logger example
	LOG_INFO << "Program started";
	MainUI ab;
	ab.activateUI(argc, argv);

	return 0;
}


