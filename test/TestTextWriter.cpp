#include "TestTextWriter.h"

bool Mitrais::test::TestTextWriter::isExist(std::string filePath)
{
	 struct stat buffer;
	 return (stat (filePath.c_str(), &buffer) == 0);
}

void Mitrais::test::TestTextWriter::testTextWriterOne()
{
	Mitrais::util::TextWriter writer;
	Mitrais::util::BaseResponse response;

	std::string filePath = "./test writer one";
	std::string content = "www.google.com";

	writer.setFilePath(filePath);
	writer.setContent(content);

	writer.writeToFile(response, false);

	bool actual = true;
	bool result = isExist(filePath);
	CPPUNIT_ASSERT(result == actual);
}

void Mitrais::test::TestTextWriter::testTextWriterTwo()
{
	Mitrais::util::TextWriter writer;
	Mitrais::util::BaseResponse response;

	std::string filePath = "./test writer one";
	std::string actual = "www.google.com";

	// read the file
	std::ifstream file(filePath);

	std::string result;

	if (file.is_open())
	{
		std::getline(file, result);

		file.close();
	}

	int isEqual = result.compare(actual);
	CPPUNIT_ASSERT(isEqual == 0);
}

void Mitrais::test::TestTextWriter::testWriteToDB()
{
	Mitrais::util::TextWriter writer;
	const std::string dbHost = "localhost";
	const int dbPort = 27017;
	const std::string dbName = "SpiderBite";
	DB::Connector connector(dbHost, dbPort, dbName);
	DB::Website website;

	std::string content = "This is from unit test textwriter save to DB";

	website.protocolType = "http";
	website.url = "www.google.com";
	website.content = content;

	connector.Insert(website);

	bool actual = true;
	bool result = connector.checkIsExist(content);
	CPPUNIT_ASSERT(result == actual);
}

void Mitrais::test::TestTextWriter::testReplaceAll()
{
	const std::string& old_ = "/";
	const std::string& new_ = "_";
	Mitrais::util::TextWriter writer;
	CPPUNIT_ASSERT(writer.replaceAll("test/test/test/test", "/", "_") == "test_test_test_test");
	CPPUNIT_ASSERT(writer.replaceAll("google.com/eu/path/to/whatever", "/", "_") == "google.com_eu_path_to_whatever");
}

void Mitrais::test::TestTextWriter::testReplaceFirst()
{
	Mitrais::util::TextWriter writer;
	CPPUNIT_ASSERT(writer.replaceFirst("wenn hinter fliegen fliegen fliegen, fliegen fliegen fliegen hinterher!", "fliegen", "test")
			== "wenn hinter test fliegen fliegen, fliegen fliegen fliegen hinterher!");
	CPPUNIT_ASSERT(writer.replaceFirst("http://www.google.com", "http://", "") == "www.google.com");
	CPPUNIT_ASSERT(writer.replaceFirst("www.google.com", "www.", "") == "google.com");
	CPPUNIT_ASSERT(writer.replaceFirst("www.google.com", "", "test") == "www.google.com");
}
