/*
 * TestXMLHelper.h
 *
 *  Created on: Jul 18, 2016
 *      Author: developer
 */

#ifndef TEST_TESTXMLHELPER_H_
#define TEST_TESTXMLHELPER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../inc/util/XMLHelper.h"

namespace Mitrais{
	namespace test{
		class TestXMLHelper : public CppUnit::TestFixture
		{
		public:
			CPPUNIT_TEST_SUITE(TestXMLHelper);
			CPPUNIT_TEST(testXMLHelperOne);
			CPPUNIT_TEST(testXMLHelperTwo);
			CPPUNIT_TEST_SUITE_END();

		private:
			void testXMLHelperOne();
			void testXMLHelperTwo();
		};
		CPPUNIT_TEST_SUITE_REGISTRATION( TestXMLHelper );
	}
}



#endif /* TEST_TESTXMLHELPER_H_ */
