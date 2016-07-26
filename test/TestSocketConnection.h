/*
 * TestSocketConnection.h
 *
 *  Created on: Jun 16, 2016
 *      Author: Ari Suarkadipa
 */

#ifndef TEST_TESTSOCKETCONNECTION_H_
#define TEST_TESTSOCKETCONNECTION_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../inc/util/SocketConnection.h"


class TestSocketConnection: public CppUnit::TestFixture
{
public:

	CPPUNIT_TEST_SUITE(TestSocketConnection);
	CPPUNIT_TEST(testSocketConnectionOne);
	CPPUNIT_TEST(testSocketConnectionTwo);
	CPPUNIT_TEST_SUITE_END();


private:
	void testSocketConnectionOne();
	void testSocketConnectionTwo();

};

CPPUNIT_TEST_SUITE_REGISTRATION( TestSocketConnection );




#endif /* TEST_TESTSOCKETCONNECTION_H_ */
