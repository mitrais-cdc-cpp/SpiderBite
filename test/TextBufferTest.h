/*
 * TextBufferTest.h
 *
 *  Created on: Jun 23, 2016
 *      Author: developer
 */

#ifndef TEST_TEXTBUFFERTEST_H_
#define TEST_TEXTBUFFERTEST_H_

#include <cppunit/TestCase.h>
#include "../inc/TextBuffer.h"

using namespace Mitrais::util;

namespace Mitrais
{
namespace test
{
	class TextBufferTest : public CppUnit::TestCase
	{
		public:
			TextBufferTest();
			~TextBufferTest();

			void runTest()
			{
				string test_data1="This is the first paragraph";
				string test_data2="This is the second paragraph";
				TextBuffer buffer;

				string result = test_data1.append(test_data2);
				buffer.insertContentToBuffer(test_data1);
				buffer.insertContentToBuffer(test_data2);

				CPPUNIT_ASSERT(buffer.getFullContent() == result);
			}
	};

}
}

#endif /* TEST_TEXTBUFFERTEST_H_ */
