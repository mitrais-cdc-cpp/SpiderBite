/*
 * TestXMLHelper.cpp
 *
 *  Created on: Jul 18, 2016
 *      Author: developer
 */

#include "../inc/XMLHelper.h"
#include "../inc/Logger.h"
#include "TestXMLHelper.h"

using namespace Mitrais::test;
using namespace Mitrais::util;

void TestXMLHelper::testXMLHelperOne()
{
	XMLHelper helper;
	ConfigSettings cf(
			"constring_test",
			"log_name",
			3,
			SAVE_TO_DB,
			"path_loc");
	string fileName = "testConfig.xml";

	helper.saveXML(cf, fileName.c_str());
	ifstream f(fileName.c_str());

	bool isExist = f.good();
	CPPUNIT_ASSERT(isExist == 1);
}

void TestXMLHelper::testXMLHelperTwo()
{
	XMLHelper helper;
	string fileName = "testConfig.xml";
	ConfigSettings newCf;

	helper.loadXML(newCf, fileName.c_str());
	const string testData = "constring_test";
	bool isTrue = newCf.connectionString.compare(testData);
	CPPUNIT_ASSERT(isTrue == 0);
}
