#ifndef SPIDERBITE_TEST_TESTTEXTLEXER_H_
#define SPIDERBITE_TEST_TESTTEXTLEXER_H_

#include <fstream>
#include <string>
#include <iostream>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../inc/util/TextLexer.h"

class TestTextLexer: public CppUnit::TestFixture
{
public:

	CPPUNIT_TEST_SUITE(TestTextLexer);
	CPPUNIT_TEST(testTextLexerStatusTrue);
	CPPUNIT_TEST(testTextLexerMessageSuccess);
	CPPUNIT_TEST(testTextLexerResultOne);
	CPPUNIT_TEST(testTextLexerResultTwo);
	CPPUNIT_TEST_SUITE_END();

private:
	std::vector<std::string> findUrls();
	std::vector<std::string> findUrls(Mitrais::util::BaseResponse& response);
	void testTextLexerStatusTrue();
	void testTextLexerMessageSuccess();
	void testTextLexerResultOne();
	void testTextLexerResultTwo();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestTextLexer );

#endif /* SPIDERBITE_TEST_TESTTEXTLEXER_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
