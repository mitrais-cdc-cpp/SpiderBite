#ifndef SPIDERBITE_TEST_TESTWEBCRAWLER_H_
#define SPIDERBITE_TEST_TESTWEBCRAWLER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../inc/util/WebCrawler.h"

class TestWebCrawler: public CppUnit::TestFixture
{
public:

	CPPUNIT_TEST_SUITE(TestWebCrawler);
	CPPUNIT_TEST(testWebCrawlerStatusNone);
	//CPPUNIT_TEST(testWebCrawlerStatusDone);
	CPPUNIT_TEST(testWebCrawlerStatusError);
	CPPUNIT_TEST_SUITE_END();

private:
	void testWebCrawlerStatusNone();
	void testWebCrawlerStatusDone();
	void testWebCrawlerStatusError();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestWebCrawler );

#endif /* SPIDERBITE_TEST_TESTWEBCRAWLER_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
