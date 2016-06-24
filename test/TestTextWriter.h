/*
 * TestTextWriter.h
 *
 *  Created on: Jun 24, 2016
 *      Author: Ari Suarkadipa
 */

#ifndef TEST_TESTTEXTWRITER_H_
#define TEST_TESTTEXTWRITER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../inc/TextWriter.h"
#include <sys/stat.h>

class TestTextWriter : public CppUnit::TestFixture
{
	public:
		CPPUNIT_TEST_SUITE(TestTextWriter);
		CPPUNIT_TEST(testTextWriterOne);
		CPPUNIT_TEST(testTextWriterTwo);
		CPPUNIT_TEST_SUITE_END();

	private:
		void testTextWriterOne();
		void testTextWriterTwo();
		bool isExist(string filePath);
};
CPPUNIT_TEST_SUITE_REGISTRATION( TestTextWriter );

#endif /* TEST_TESTTEXTWRITER_H_ */
