#include "TestTextLexer.h"

/*
 * Get urls record without response
 */
std::vector<std::string> TestTextLexer::findUrls()
{
	std::fstream file("Mitrais.html");
	std::string content;
	content.assign((std::istreambuf_iterator<char>(file) ),
            		(std::istreambuf_iterator<char>()));

	Mitrais::util::TextLexer lexer(content);
	file.close();
	return lexer.findUrls();
}

/*
 * Get urls record and the response message
 */
std::vector<std::string> TestTextLexer::findUrls(Mitrais::util::BaseResponse& response)
{
	std::fstream file("Mitrais.html");
	std::string content;
	content.assign((std::istreambuf_iterator<char>(file) ),
	            		(std::istreambuf_iterator<char>()));

	Mitrais::util::TextLexer lexer(content);
	file.close();
	return lexer.findUrls(response);
}

/*
 * test whether the status is true or not
 */
void TestTextLexer::testTextLexerStatusTrue()
{
	Mitrais::util::BaseResponse response;
	std::vector<std::string> results = findUrls(response);
	bool status = response.getStatus();

	CPPUNIT_ASSERT(status == true);
}

/*
 * test return message whether "Success" or not
 */
void TestTextLexer::testTextLexerMessageSuccess()
{

	Mitrais::util::BaseResponse response;
	std::vector<std::string> results = findUrls(response);

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
 * test the result of text reader 1st record
 */
void TestTextLexer::testTextLexerResultOne()
{
	Mitrais::util::BaseResponse response;
	std::vector<std::string> results = findUrls(response);

	std::string actualResult = "https://www.linkedin.com/company/mitrais";

	int isEqual = results.at(0).compare(actualResult);

	CPPUNIT_ASSERT(isEqual == 0);
}

/*
 * test the result of text reader 2nd record
 */
void TestTextLexer::testTextLexerResultTwo()
{
	Mitrais::util::BaseResponse response;
	std::vector<std::string> results = findUrls(response);

	std::string actualResult = "https://www.facebook.com/Mitrais";

	int isEqual = results.at(1).compare(actualResult);

	CPPUNIT_ASSERT(isEqual == 0);
}
