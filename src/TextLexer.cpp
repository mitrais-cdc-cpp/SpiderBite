#include "../inc/TextLexer.h"



/*
 * TextLexer default constructor
 */
Mitrais::util::TextLexer::TextLexer()
{

}

/*
 * TextLexer constructor with parameter
 * @params content
 */
Mitrais::util::TextLexer::TextLexer(std::string content)
: _content(content)
{

}

/*
 * TextLexer desctructor
 */
Mitrais::util::TextLexer::~TextLexer()
{

}

/*
 * setContent function to set the content
 */
void Mitrais::util::TextLexer::setContent(std::string content)
{
	// set the file path
	_content = content;
}

/*
 * findUrls function to get the vector of URL target
 * read from file that has been set the file path
 * @returns  urls
 */
std::vector<std::string> Mitrais::util::TextLexer::findUrls()
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
 * @returns urls
 */
std::vector<std::string> Mitrais::util::TextLexer::findUrls(BaseResponse& response)
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
		LOG_INFO << "Success find all urls from the content";
	}
	catch (std::exception& ex)
	{
		// catch the exception
		std::string message = string(ex.what());
		
		response.addMessage(message);

		// set the status to be false
		response.updateStatus(false);

		// log error message
		LOG_ERROR << message;
	}

	return urls;
}

/*
 * findUrls function with parameter to get vector of URL target also get response message
 * @params content
 * @return urls
 */
std::vector<std::string> Mitrais::util::TextLexer::findUrls(std::string content)
{
	setContent(content);

	return findUrls();
}

/*
 * findUrls function with parameter to get vector of URL target also get response message
 * @params content
 * @params response
 * @return vector<std::string> urls
 */
std::vector<std::string> Mitrais::util::TextLexer::findUrls(std::string content, BaseResponse& response)
{
	setContent(content);

	return findUrls(response);
}

/*
 * readContent function to read the file and save into vector
 * @return urls
 */
std::vector<std::string> Mitrais::util::TextLexer::readContent()
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

	// define the regex pattern for the link
	boost::regex urlRegex{"<a href=\"(http|ftp|https|www|gopher|telnet|file)(.*?)\">"};

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
			std::string url = string(what[0]);

			urls.push_back(getUrl(url));
		}
	}

	return urls;
}

/*
 * get url fucntion
 * @params hyperlink
 */
std::string Mitrais::util::TextLexer::getUrl(std::string hyperlink)
{
	// define the regex pattern for the link
	boost::regex urlRegex{"\"(http|ftp|https|www|gopher|telnet|file)(.*?)\""};

	boost::smatch urlMatchResult;
	boost::match_results<std::string::const_iterator> what;
	boost::match_flag_type flags = boost::match_default;
	std::string::const_iterator start;
	std::string::const_iterator end;

	std::string line;

	start = hyperlink.begin();
	end = hyperlink.end();

	if (boost::regex_search(start, end, what, urlRegex, flags))
	{
		line = std::string(what[0]);

		// remove the " character from the url
		line.erase(std::remove(line.begin(), line.end(), '\"'), line.end());
	}

	return line;
}
