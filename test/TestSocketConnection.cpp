#include "TestSocketConnection.h"
#include "../inc/SocketConnection.h"


void TestSocketConnection::testSocketConnectionOne()
{
	Mitrais::util::SocketConnection test("www.google.com");
	bool isOpen = test.isSocketOpen();
	CPPUNIT_ASSERT(isOpen==true);
}

void TestSocketConnection::testSocketConnectionTwo()
{
	Mitrais::util::SocketConnection test("http://www.google.com");
	bool isOpen = test.isSocketOpen();
	CPPUNIT_ASSERT(isOpen==false);
}
