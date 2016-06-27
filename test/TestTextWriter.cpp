/*
 * TestTextWriter.cpp
 *
 *  Created on: Jun 24, 2016
 *      Author: Ari Suarkadipa
 */

#include "../inc/TextWriter.h"
#include "TestTextWriter.h"

bool TestTextWriter::isExist(string filePath)
{
	 struct stat buffer;
	 return (stat (filePath.c_str(), &buffer) == 0);
}

void TestTextWriter::testTextWriterOne()
{
	Mitrais::util::TextWriter writer;
	Mitrais::util::BaseResponse response;

	string filePath = "./test writer one";
	string content = "www.google.com";

	writer.setFilePath(filePath);
	writer.setContent(content);

	writer.writeToFile(response, false);

	bool actual = true;
	bool result = isExist(filePath);
	CPPUNIT_ASSERT(result == actual);
}

void TestTextWriter::testTextWriterTwo()
{
	Mitrais::util::TextWriter writer;
	Mitrais::util::BaseResponse response;

	string filePath = "./test writer one";
	string actual = "www.google.com";

	// read the file
	std::ifstream file(filePath);

	string result;

	if (file.is_open())
	{
		std::getline(file, result);

		file.close();
	}

	int isEqual = result.compare(actual);
	CPPUNIT_ASSERT(isEqual == 0);
}


