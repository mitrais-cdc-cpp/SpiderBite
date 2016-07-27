#ifndef SPIDERBITE_INC_TEXTREADER_H_
#define SPIDERBITE_INC_TEXTREADER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <boost/regex.hpp>
#include <vector>
#include <sys/stat.h>
#include <algorithm>

#include "Poco/URI.h"
#include "Poco/Exception.h"

#include "BaseResponse.h"
#include "UrlTarget.h"
#include "Logger.h"

namespace Mitrais
{
namespace util
{

class TextReader
{
public:

	TextReader();
	TextReader(std::string filePath);
	~TextReader();

	void setFilePath(std::string filePath);
	std::vector<UrlTarget> getUrls();
	std::vector<UrlTarget> getUrls(BaseResponse& response);
	std::vector<UrlTarget> getUrls(std::string filePath);
	std::vector<UrlTarget> getUrls(std::string filePath, BaseResponse& response);
	static UrlTarget getUrl(std::string url);
	static bool isUrlExist(const vector<UrlTarget>& existingUrls, const UrlTarget& currentUrl);

private:
	std::string _filePath;
	std::vector<UrlTarget> _targets;
	bool isExist(std::string filePath);
	std::vector<UrlTarget> readFile();
	bool checkDuplicateUrl(std::string url, UrlTarget& target);
	static std::string removeUrlPrefix(std::string url);
};

}
} //namespace Mitrais::util


#endif /* SPIDERBITE_INC_TEXTREADER_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
