#include "../inc/TextReader.h"

namespace Mitrais
{
namespace util
{

TextReader::TextReader()
{

}

TextReader::TextReader(std::string filePath)
{
	_filePath = filePath;
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

	std::ifstream file(_filePath);
	std::string url;

	std::regex urlRegex (
			    R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)",
			    std::regex::extended
			  );

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

std::vector<std::string> TextReader::getUrls(std::string filePath)
{
	TextReader::setFilePath(filePath);

	return TextReader::getUrls();
}

}}/* namespace Mitrais::util */
