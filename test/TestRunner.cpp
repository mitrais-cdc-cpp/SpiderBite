/*
 * TestSocketConnectionRunner.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: Ari Suarkadipa
 */

#include <iostream>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include "TestSocketConnection.h"

namespace Mitrais
{
namespace test
{
	int main()
	{
		CppUnit::TextUi::TestRunner runner;
		runner.addTest(new TestSocketConnection());
		runner.addTest(new TextReaderTest());
		runner.run();

		return 0;
	}
}
}
