#include "../inc/TextReader.h"

namespace Mitrais
{
namespace util
{

/*
 * TextReader default constructor
 */
TextReader::TextReader()
{

}

/*
 * TextReader constructor with parametere
 * @parameter string filePath
 */
TextReader::TextReader(std::string filePath) :
		_filePath(filePath)
{

}

/*
 * TextReader desctructor
 */
TextReader::~TextReader()
{

}

/*
 * setFilePath function to set the file path of the file
 * @return void
 */
void TextReader::setFilePath(std::string filePath)
{
	// set the file path
	_filePath = filePath;
}

/*
 * getUrls function to get the vector of URL target
 * read from file that has been set the file path
 * @return vector<UrlTarget> urls
 */
std::vector<UrlTarget> TextReader::getUrls()
{
	std::vector<UrlTarget> urls;

	// check file is exist or not
	bool isFileExist = isExist(_filePath);

	if (isFileExist)
	{
		urls = readFile();
	}

	return urls;
}

/*
 * getUrls function with parameter to get vector of URL target also get response message
 *  * @return vector<UrlTarget> urls
 */
std::vector<UrlTarget> TextReader::getUrls(BaseResponse& response)
{
	std::vector<UrlTarget> urls;

	try
	{
		// check if the file is exist or not
		bool isFileExist = isExist(_filePath);

		if (!isFileExist)
		{
			// add response message
			response.addMessage("The file : "+ _filePath +" does not exist");

			// update the status into glase
			response.updateStatus(false);

			return urls;
		}

		// read the file
		urls = readFile();

		// set the status into true
		response.updateStatus(true);

		// add success message
		response.addSuccessMessage();
	}
	catch (std::exception& ex)
	{
		// catch the exception
		response.addMessage(ex.what());

		// set the status to be false
		response.updateStatus(false);
	}

	return urls;
}

/*
 * getUrls function with parameter to get vector of URL target also get response message
 * @param string filePath
 * @return vector<UrlTarget> urls
 */
std::vector<UrlTarget> TextReader::getUrls(std::string filePath)
{
	setFilePath(filePath);

	return getUrls();
}

/*
 * getUrls function with parameter to get vector of URL target also get response message
 * @param string filePath
 * @param BaseResponse response
 * @return vector<UrlTarget> urls
 */
std::vector<UrlTarget> TextReader::getUrls(std::string filePath, BaseResponse& response)
{
	setFilePath(filePath);

	return getUrls(response);
}

/*
 * isExist function to check if file is exist or not
 * @param string filePath
 * @return bool status
 */
bool TextReader::isExist(std::string filePath)
{
	 struct stat buffer;
	 return (stat (filePath.c_str(), &buffer) == 0);
}

/*
 * readFile function to read the file and save into vector
 * @return vector<UrlTarget> urls
 */
std::vector<UrlTarget> TextReader::readFile()
{
	std::vector<UrlTarget> urls;

	// read the file
	std::ifstream file(_filePath);
	std::string url;

	// define the regex pattern
	boost::regex urlRegex{".*\\..*"};

	boost::smatch urlMatchResult;

	if (file.is_open())
	{
		while (std::getline(file, url))
		{
			// check if the url is match with regex pattern
			if (boost::regex_match(url, urlMatchResult, urlRegex))
			{
				UrlTarget target;

				if (!url.empty() && url[url.size() - 1] == '\r')
					url.erase(url.size() - 1);

				if (!url.empty() && url[url.size() - 1] == '\n')
					url.erase(url.size() - 1);

				target.Url = url;
				target.LatestUrlPosition = url;
				target.Status = NONE;

				// store into vector
				urls.push_back(target);
			}
		}

		file.close();
	}

	return urls;
}

}}/* namespace Mitrais::util */
