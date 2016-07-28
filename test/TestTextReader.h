#ifndef SPIDERBITE_TEST_TESTTEXTREADER_H_
#define SPIDERBITE_TEST_TESTTEXTREADER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../inc/TextReader.h"
#include "../inc/UrlTarget.h"

class TestTextReader: public CppUnit::TestFixture
{
public:

	CPPUNIT_TEST_SUITE(TestTextReader);
	CPPUNIT_TEST(testTextReaderStatusTrue);
	CPPUNIT_TEST(testTextReaderMessageSuccess);
	CPPUNIT_TEST(testTextReaderResultNumber);
	CPPUNIT_TEST(testTextReaderResultOne);
	CPPUNIT_TEST(testTextReaderResultTwo);
	CPPUNIT_TEST(testTextReaderDuplicateUrl);
	CPPUNIT_TEST_SUITE_END();

private:
	std::vector<Mitrais::util::UrlTarget> getUrls();
	std::vector<Mitrais::util::UrlTarget> getUrls(Mitrais::util::BaseResponse& response);
	void testTextReaderStatusTrue();
	void testTextReaderMessageSuccess();
	void testTextReaderResultNumber();
	void testTextReaderResultOne();
	void testTextReaderResultTwo();
	void testTextReaderDuplicateUrl();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestTextReader );

#endif /* SPIDERBITE_TEST_TEXTREADERTEST_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
