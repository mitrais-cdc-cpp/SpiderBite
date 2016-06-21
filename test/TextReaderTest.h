#ifndef SPIDERBITE_TEST_TEXTREADERTEST_H_
#define SPIDERBITE_TEST_TEXTREADERTEST_H_

#include <cppunit/TestCase.h>
#include "../inc/TextReader.h"

using namespace Mitrais::util;

namespace Mitrais
{
namespace test
{
	class TextReaderTest : public CppUnit::TestCase
	{
		public:
			TextReaderTest();
			~TextReaderTest();

			void runTest()
			{
				Mitrais::util::TextReader reader("testUrl.txt");

				vector<util::UrlTarget> actual;
				util::UrlTarget url1;
				url1.Url = "http://mitrais.com";
				url1.LatestUrlPosition = "http://mitrais.com";
				url1.Status = NONE;

				actual.push_back(url1);

				CPPUNIT_ASSERT(reader.getUrls()[0].Url == actual[0].Url);
			}
	};

}
}

#endif /* SPIDERBITE_TEST_TEXTREADERTEST_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
