#include "TestTextReader.h"

/*
 * Get urls record without response
 */
std::vector<Mitrais::util::UrlTarget> TestTextReader::getUrls()
{
	Mitrais::util::TextReader reader("testUrl.txt");
	return reader.getUrls();
}

/*
 * Get urls record and the response message
 */
std::vector<Mitrais::util::UrlTarget> TestTextReader::getUrls(Mitrais::util::BaseResponse& response)
{
	Mitrais::util::TextReader reader("testUrl.txt");
	return reader.getUrls(response);
}

/*
 * test whether the status is true or not
 */
void TestTextReader::testTextReaderStatusTrue()
{
	Mitrais::util::BaseResponse response;
	std::vector<Mitrais::util::UrlTarget> results = getUrls(response);
	bool status = response.getStatus();

	CPPUNIT_ASSERT(status == true);
}

/*
 * test return message whether "Success" or not
 */
void TestTextReader::testTextReaderMessageSuccess()
{

	Mitrais::util::BaseResponse response;
	std::vector<Mitrais::util::UrlTarget> results = getUrls(response);

	std::string actualMessage = "Success";

	std::string resultMessage;
	if (response.getStatus())
	{
		std::vector<string> messages = response.getMessages();

		if (messages.size() == 1)
		{
			resultMessage = messages.at(0);
		}
	}

	int isEqual = resultMessage.compare(actualMessage);

	CPPUNIT_ASSERT(isEqual == 0);
}

/*
 * test the result number of url record on file
 */
void TestTextReader::testTextReaderResultNumber()
{
	Mitrais::util::BaseResponse response;
	std::vector<Mitrais::util::UrlTarget> results = getUrls(response);

	int actualResultNumber(2);

	int resultNumber = results.size();

	CPPUNIT_ASSERT(resultNumber == actualResultNumber);
}

/*
 * test the result of text reader 1st record
 */
void TestTextReader::testTextReaderResultOne()
{
	Mitrais::util::BaseResponse response;
	std::vector<Mitrais::util::UrlTarget> results = getUrls(response);

	std::string actualResult = "www.google.com";

	int isEqual = results.at(0).Url.compare(actualResult);

	CPPUNIT_ASSERT(isEqual == 0);
}

/*
 * test the result of text reader 2nd record
 */
void TestTextReader::testTextReaderResultTwo()
{
	Mitrais::util::BaseResponse response;
	std::vector<Mitrais::util::UrlTarget> results = getUrls(response);

	std::string actualResult = "http://mitrais.com";

	int isEqual = results.at(1).Url.compare(actualResult);

	CPPUNIT_ASSERT(isEqual == 0);
}
