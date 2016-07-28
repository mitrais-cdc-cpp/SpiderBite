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
			"localhost",
			5000,
			"SpiderBiteTest",
			"SpiderBiteTest",
			3,
			SAVE_TO_DB,
			"/home/test_result/");
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
	bool isTrue = newCf.dbHost.compare(testData);
	CPPUNIT_ASSERT(isTrue == 0);
}
