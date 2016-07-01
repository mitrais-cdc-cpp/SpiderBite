/*
 * TextLexer.h
 *
 *  Created on: Jun 24, 2016
 *      Author: developer
 */

#ifndef SPIDERBITE_INC_TEXTLEXER_H_
#define SPIDERBITE_INC_TEXTLEXER_H_

#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <vector>
#include <regex>

#include "Logger.h"

#include "BaseResponse.h"

using namespace std;

namespace Mitrais
{
namespace util
{

class TextLexer
{
public:

	TextLexer();
	TextLexer(std::string content);
	~TextLexer();

	void setContent(std::string content);
	std::vector<string> findUrls();
	std::vector<string> findUrls(BaseResponse& response);
	std::vector<std::string> findUrls(std::string content);
	std::vector<std::string> findUrls(std::string content, BaseResponse& response);

private:
	std::string _content;
	std::vector<string> readContent();
};

}
} //namespace Mitrais::util


#endif /* SPIDERBITE_INC_TEXTLEXER_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
