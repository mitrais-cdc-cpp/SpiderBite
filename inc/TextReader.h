#ifndef SPIDERBITE_INC_TEXTREADER_H_
#define SPIDERBITE_INC_TEXTREADER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <sys/stat.h>

#include "BaseResponse.h"

using namespace std;

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
	std::vector<std::string> getUrls();
	std::vector<std::string> getUrls(BaseResponse& response);
	std::vector<std::string> getUrls(std::string filePath);
	std::vector<std::string> getUrls(std::string filePath, BaseResponse& response);

private:
	std::string _filePath;
	bool isExist(std::string filePath);
	std::vector<std::string> readFile();
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
