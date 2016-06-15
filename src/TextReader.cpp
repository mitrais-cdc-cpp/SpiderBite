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

std::vector<std::string> TextReader::getUrls()
{
	std::vector<std::string> urls;

	bool isFileExist = isExist(_filePath);

	if (!isFileExist)
	{
		return urls;
	}

	urls = readFile();

	return urls;
}

std::vector<std::string> TextReader::getUrls(BaseResponse& response)
{
	std::vector<std::string> urls;

	try
	{
		bool isFileExist = isExist(_filePath);

		if (!isFileExist)
		{
			response.addMessage("The file : "+_filePath +" does not exist");
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

std::vector<std::string> TextReader::getUrls(std::string filePath)
{
	setFilePath(filePath);

	return getUrls();
}

std::vector<std::string> TextReader::getUrls(std::string filePath, BaseResponse& response)
{
	setFilePath(filePath);

	return getUrls(response);
}

bool TextReader::isExist(std::string filePath)
{
	 struct stat buffer;
	 return (stat (filePath.c_str(), &buffer) == 0);
}

std::vector<std::string> TextReader::readFile()
{
	std::vector<std::string> urls;

	std::ifstream file(_filePath);
	std::string url;

	std::regex urlRegex(".*\\..*");

	std::smatch urlMatchResult;

	while (std::getline(file, url))
	{
		if (std::regex_match(url, urlMatchResult, urlRegex))
		{
			urls.push_back(url);
		}
	}

	return urls;
}

}}/* namespace Mitrais::util */
