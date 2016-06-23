
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "TestSocketConnection.h"
#include "../inc/SocketConnection.h"
#include "TestTextReader.h"
#include "../inc/TextReader.h"
#include "TestTextBuffer.h"
#include "../inc/TextBuffer.h"

using namespace Mitrais::util;

int main()
{
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

	runner.addTest( registry.makeTest() );
	bool wasSuccessful = runner.run();

	return 0;
}


