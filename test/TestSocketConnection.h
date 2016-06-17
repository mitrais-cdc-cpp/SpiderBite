/*
 * TestSocketConnection.h
 *
 *  Created on: Jun 16, 2016
 *      Author: Ari Suarkadipa
 */

#ifndef TEST_TESTSOCKETCONNECTION_H_
#define TEST_TESTSOCKETCONNECTION_H_

#include <cppunit/TestCase.h>
#include "../inc/SocketConnection.h"

namespace Mitrais
{
namespace test
{
	class TestSocketConnection: public CppUnit::TestCase
	{
	public:
		TestSocketConnection();
		~TestSocketConnection();

		void runTest()
		{
			Mitrais::util::SocketConnection socket;

			socket.setServerName("www.google.com");
			CPPUNIT_ASSERT(socket.isSocketOpen()==true);

			socket.setServerName("http://www.google.com");
			CPPUNIT_ASSERT(socket.isSocketOpen()==false);
		}
	};
}
}



#endif /* TEST_TESTSOCKETCONNECTION_H_ */
