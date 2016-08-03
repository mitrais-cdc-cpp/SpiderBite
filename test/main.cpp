
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../inc/SocketConnection.h"

using namespace Mitrais::util;

int main()
{
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

	runner.addTest( registry.makeTest() );
	bool wasSuccessful = runner.run();

	return 0;
}
