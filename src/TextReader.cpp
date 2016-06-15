#include "../inc/TextReader.h"

namespace Mitrais
{
namespace util
{

TextReader::TextReader()
{

}

TextReader::TextReader(std::string filePath) :
		_filePath(filePath)
{

}

TextReader::~TextReader()
{

}

void TextReader::setFilePath(std::string filePath)
{
	_filePath = filePath;
}

std::vector<UrlTarget> TextReader::getUrls()
{
	std::vector<UrlTarget> urls;

	bool isFileExist = isExist(_filePath);

	if (isFileExist)
	{
		urls = readFile();
	}

	return urls;
}

std::vector<UrlTarget> TextReader::getUrls(BaseResponse& response)
{
	std::vector<UrlTarget> urls;

	try
	{
		bool isFileExist = isExist(_filePath);

		if (!isFileExist)
		{
			response.addMessage("The file : "+ _filePath +" does not exist");
			response.updateStatus(false);
			return urls;
		}

		urls = readFile();

		response.updateStatus(true);
		response.addSuccessMessage();
	}
	catch (std::exception& ex)
	{
		response.addMessage(ex.what());
		response.updateStatus(false);
	}

	return urls;
}

std::vector<UrlTarget> TextReader::getUrls(std::string filePath)
{
	setFilePath(filePath);

	return getUrls();
}

std::vector<UrlTarget> TextReader::getUrls(std::string filePath, BaseResponse& response)
{
	setFilePath(filePath);

	return getUrls(response);
}

bool TextReader::isExist(std::string filePath)
{
	 struct stat buffer;
	 return (stat (filePath.c_str(), &buffer) == 0);
}

std::vector<UrlTarget> TextReader::readFile()
{
	std::vector<UrlTarget> urls;

	std::ifstream file(_filePath);
	std::string url;

	boost::regex urlRegex{".*\\..*"};

	boost::smatch urlMatchResult;

	while (std::getline(file, url))
	{
		if (boost::regex_match(url, urlMatchResult, urlRegex))
		{
			UrlTarget target;

			target.Url = url;
			target.LatestUrlPosition = url;
			target.Status = NONE;

			urls.push_back(target);
		}
	}

	return urls;
}

}}/* namespace Mitrais::util */
