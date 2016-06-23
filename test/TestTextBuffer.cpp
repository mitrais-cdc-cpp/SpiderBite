/*
 * TextBufferTest.cpp
 *
 *  Created on: Jun 23, 2016
 *      Author: developer
 */

#include "../inc/TextBuffer.h"
#include "TestTextBuffer.h"

void TestTextBuffer::testTextBufferOne()
{
	string test_data1="This is the first paragraph";
	string test_data2="This is the second paragraph";
	Mitrais::util::TextBuffer buffer;

	buffer.insertContentToBuffer(test_data1);
	buffer.insertContentToBuffer(test_data2);

	string result = test_data1.append(test_data2);
	string content = buffer.getFullContent();

	bool isTrue = content.compare(result);
	CPPUNIT_ASSERT(isTrue == 0);
}

void TestTextBuffer::testTextBufferTwo()
{
	string test_data1="This is the first paragraph";
	string test_data2="This is the second paragraph";
	Mitrais::util::TextBuffer buffer;

	buffer.insertContentToBuffer(test_data1);

	string result = test_data1.append(test_data2);
	string content = buffer.getFullContent();

	bool isFalse = content.compare(result);
	CPPUNIT_ASSERT(isFalse == 1);
}

