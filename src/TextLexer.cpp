#include "../inc/TextLexer.h"

namespace Mitrais
{
namespace util
{

/*
 * TextLexer default constructor
 */
TextLexer::TextLexer()
{

}

/*
 * TextLexer constructor with parameter
 * @parameter string content
 */
TextLexer::TextLexer(std::string content) :
		_content(content)
{

}

/*
 * TextLexer desctructor
 */
TextLexer::~TextLexer()
{

}

/*
 * setContent function to set the content
 * @return void
 */
void TextLexer::setContent(std::string content)
{
	// set the file path
	_content = content;
}

/*
 * findUrls function to get the vector of URL target
 * read from file that has been set the file path
 * @return vector<std::string> urls
 */
std::vector<std::string> TextLexer::findUrls()
{
	std::vector<std::string> urls;

	// check the content
	bool isContentEmpty = _content.empty();

	if (!isContentEmpty)
	{
		urls = readContent();
	}

	return urls;
}

/*
 * findUrls function with parameter to get vector of url target also get response message
 *  * @return vector<std::string> urls
 */
std::vector<std::string> TextLexer::findUrls(BaseResponse& response)
{
	std::vector<std::string> urls;

	try
	{
		// check content (empty or not)
		bool isContentEmpty = _content.empty();

		if (isContentEmpty)
		{
			std::string message = "The content is empty";

			// add response message
			response.addMessage(message);

			// update the status into glase
			response.updateStatus(false);

			// log error message
			//LOG_ERROR << message;
		}

		// read the file
		urls = readContent();

		// set the status into true
		response.updateStatus(true);

		// add success message
		response.addSuccessMessage();

		// log success message
		//LOG_INFO << "Success find all urls from the content";
	}
	catch (std::exception& ex)
	{
		// catch the exception
		std::string message = string(ex.what());
		
		response.addMessage(message);

		// set the status to be false
		response.updateStatus(false);

		// log error message
		//LOG_ERROR << message;
	}

	return urls;
}

/*
 * findUrls function with parameter to get vector of URL target also get response message
 * @param string content
 * @return vector<std::string> urls
 */
std::vector<std::string> TextLexer::findUrls(std::string content)
{
	setContent(content);

	return findUrls();
}

/*
 * findUrls function with parameter to get vector of URL target also get response message
 * @param string content
 * @param BaseResponse response
 * @return vector<std::string> urls
 */
std::vector<std::string> TextLexer::findUrls(std::string content, BaseResponse& response)
{
	setContent(content);

	return findUrls(response);
}

/*
 * readContent function to read the file and save into vector
 * @return vector<std::string> urls
 */
std::vector<std::string> TextLexer::readContent()
{
	std::vector<std::string> urls;

	bool isContentEmpty = !_content.empty();

	if (!isContentEmpty)
	{
		return urls;
	}

	// read the file
	std::istringstream wholeContent(_content);
	std::string line;

	// define the regex pattern
	boost::regex urlRegex{"(http|ftp|https|www|gopher|telnet|file)(://|.)([\\w_-]+(?:(?:\\.[\\w_-]+)‌​+))([\\w.,@?^=%&:/~+#-]*[\\w@?^=%&/~+#-])?"};

	boost::smatch urlMatchResult;
	boost::match_results<std::string::const_iterator> what;
	boost::match_flag_type flags = boost::match_default;
	std::string::const_iterator start;
	std::string::const_iterator end;

	while(std::getline(wholeContent, line))
	{
		start = line.begin();
		end = line.end();

		if (boost::regex_search(start, end, what, urlRegex, flags))
		{
			std::cout << what[0] << endl;
			// store into vector
			urls.push_back(what[0]);
		}
	}

//	std::regex urlRegex{"(http|ftp|https|www|gopher|telnet|file)(://|.)([\\w_-]+(?:(?:\\.[\\w_-]+)‌​+))([\\w.,@?^=%&:/~+#-]*[\\w@?^=%&/~+#-])?"};
//
//	std::smatch urlMatchResult;
//
//	std::string::const_iterator start;
//	std::string::const_iterator end;
//
//	while(std::getline(wholeContent, line))
//	{
//		start = line.begin();
//		end = line.end();
//
//		if (std::regex_search(start, end, urlMatchResult, urlRegex))
//		{
//			// store into vector
//			urls.push_back(urlMatchResult[0]);
//		}
//	}

	return urls;
}

}}/* namespace Mitrais::util */
