/*
 * TextBufferTest.cpp
 *
 *  Created on: Jun 23, 2016
 *      Author: developer
 */

#include "TextBufferTest.h"
#include "../inc/TextBuffer.h"

void TextBufferTest::testTextBufferOne()
{
	string test_data1="This is the first paragraph";
	string test_data2="This is the second paragraph";
	Mitrais::util::TextBuffer buffer;

	buffer.insertContentToBuffer(test_data1);
	buffer.insertContentToBuffer(test_data2);

	string result = test_data1.append(test_data2);
	string content = buffer.getFullContent();

	CPPUNIT_ASSERT(content == result);
}

void TextBufferTest::testTextBufferOne()
{
	string test_data1="This is the first paragraph";
	string test_data2="This is the second paragraph";
	Mitrais::util::TextBuffer buffer;

	buffer.insertContentToBuffer(test_data1);

	string result = test_data1.append(test_data2);
	string content = buffer.getFullContent();

	CPPUNIT_ASSERT(content != result);
}

