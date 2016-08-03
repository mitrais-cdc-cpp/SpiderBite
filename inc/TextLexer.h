#ifndef SPIDERBITE_INC_TEXTLEXER_H_
#define SPIDERBITE_INC_TEXTLEXER_H_

#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <vector>
#include <regex>
#include <iterator>

#include "BaseResponse.h"
#include "Logger.h"
#include "UrlTarget.h"
#include "TextReader.h"

namespace Mitrais {
namespace util {

class TextLexer
{
public:

	TextLexer();
	TextLexer(std::string content);
	~TextLexer();

	void setContent(std::string content);
	std::vector<UrlTarget> findUrls(const vector<UrlTarget>& existingUrls);
	std::vector<UrlTarget> findUrls(BaseResponse& response, const vector<UrlTarget>& existingUrls);
	std::vector<UrlTarget> findUrls(std::string content, const vector<UrlTarget>& existingUrls);
	std::vector<UrlTarget> findUrls(std::string content, BaseResponse& response, const vector<UrlTarget>& existingUrls);

private:
	std::string _content;
	std::vector<UrlTarget> _existingUrls;
	std::vector<UrlTarget> readContent();
	std::string getUrl(std::string hyperlink);
};

}} //namespace Mitrais::util

#endif /* SPIDERBITE_INC_TEXTLEXER_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
