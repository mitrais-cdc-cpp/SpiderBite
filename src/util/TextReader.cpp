#include "../../inc/util/TextReader.h"

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
    // log info
	LOG_INFO << "Set file that contains URL records at : " + _filePath;
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

	// log info
	LOG_INFO << "Set file that contains URL records at : " + _filePath;
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
			std::string message = "The file : "+ _filePath +" does not exist";

			// add response message
			response.addMessage(message);

			// update the status into glase
			response.updateStatus(false);

			// log the error message
			LOG_ERROR << message;

			return urls;
		}

		// read the file
		urls = readFile();

		// set the status into true
		response.updateStatus(true);

		// add success message
		response.addSuccessMessage();

		// log success read the text reader
		LOG_INFO << "Success get all URLs record from "+ _filePath;
	}
	catch (std::exception& ex)
	{
		// catch the exception
		std::string message = string(ex.what());
		
		response.addMessage(message);

		// set the status to be false
		response.updateStatus(false);

		// log the error message
		LOG_ERROR << message;
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

				bool isExist = checkDuplicateUrl(url, target);

				if (!isExist)
				{
					_targets.push_back(target);
				}
			}
		}

		file.close();
	}

	return _targets;
}

/*
 * checkDuplicateUrl function to check the duplication of an url on venctor of url
 * @param url (string)
 * @param target (UrlTarget)
 * @return status (duplicate or not)
 */
bool TextReader::checkDuplicateUrl(std::string url, UrlTarget& target)
{
	// convert the url to lower case
	boost::algorithm::to_lower(url);

	// remove \r character
	if (!url.empty() && url[url.size() - 1] == '\r')
	{
		url.erase(url.size() - 1);
	}

	// remove enter/newline character
	if (!url.empty() && url[url.size() - 1] == '\n')
	{
		url.erase(url.size() - 1);
	}

	// remove url prefix (www.)
	url = removeUrlPrefix(url);

	target = getUrl(url);

	return isUrlExist(target);
}

/*
 * getUrl to construct an url string into UrlTarget using POCO URI library
 * @param url (string)
 * @return UrlTarget
 */
UrlTarget TextReader::getUrl(string url)
{
	UrlTarget target;

	Poco::URI uri(url);

	// get the protocol/schema (http, https, ftp)
	std::string protocol = uri.getScheme();

	// check if there is a protocol or not
	if (!protocol.empty())
	{
		target.Protocol = protocol;
	}
	else
	{
		// set "http" as default protocol
		target.Protocol = _defaultProtocol;
	}

	// get the host name and also the authority or port (if exist, example : www.mitrais.com:8080)
	target.Url = uri.getAuthority();

	// remove url prefix (www.)
	target.Url = removeUrlPrefix(target.Url);

	// get the pathEtc (mitaris.com/contact-us, pathEtc = /contact-us
	std::string pathOrSubpage = uri.getPathEtc();

	// check if the pathEtc is exist
	if (!pathOrSubpage.empty())
	{
		// add into host name and auth address
		target.Url += pathOrSubpage;
	}

	// set the latest url position as the url
	target.LatestUrlPosition = target.Url;

	// set the target as NONE
	target.Status = NONE;

	return target;
}

/*
 * Check whether the url target is exist or not on vector
 * @param UrlTarget
 * @return status (exist or not)
 */
bool TextReader::isUrlExist(UrlTarget target)
{
//	vector<UrlTarget>::iterator it;
//
//	it = std::find(_targets.begin(), _targets.end(), target);
//
//	if (it !=_targets.end())
//	{
//		// if found (there is duplication)
//		return true;
//	}
//
//	// not found
//	return false;

	// looping manual to search the equal value since could not use std::find
	if (_targets.size() > 0)
	{
		for(auto const& existingUrl:_targets)
		{
			if ((existingUrl.Protocol.compare(target.Protocol) == 0) &&
				(existingUrl.Url.compare(target.Url) == 0))
			{
				return true;
			}
		}
	}

	return false;
}

std::string TextReader::removeUrlPrefix(std::string url)
{
	if (url.compare(0, _prefixLength, _prefix) == 0)
	{
		// remove the "www." character
		url.erase(0, _prefixLength);
	}

	return url;
}

}}/* namespace Mitrais::util */
