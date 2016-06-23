/*
 * TextBufferTest.h
 *
 *  Created on: Jun 23, 2016
 *      Author: developer
 */

#ifndef TEST_TESTTEXTBUFFER_H_
#define TEST_TESTTEXTBUFFER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../inc/TextBuffer.h"

class TestTextBuffer : public CppUnit::TestFixture
{
	public:
		CPPUNIT_TEST_SUITE(TestTextBuffer);
		CPPUNIT_TEST(testTextBufferOne);
		CPPUNIT_TEST(testTextBufferTwo);
		CPPUNIT_TEST_SUITE_END();

	private:
		void testTextBufferOne();
		void testTextBufferTwo();
};
CPPUNIT_TEST_SUITE_REGISTRATION( TestTextBuffer );

#endif /* TEST_TESTTEXTBUFFER_H_ */
