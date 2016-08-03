/*
 * WebCrawler.h
 *
 *  Created on: Jun 24, 2016
 *      Author: developer
 */

#ifndef INC_WEBCRAWLER_H_
#define INC_WEBCRAWLER_H_

#include <iostream>
#include <string>
#include <curl/curl.h>

#include "UrlTarget.h"
#include "Logger.h"
#include "TextLexer.h"
#include "TextReader.h"
#include "TextBuffer.h"
#include "TextWriter.h"

using namespace std;

namespace Mitrais{
namespace util{

/**
 * Class to create a HTML GET command with help of CURL.
 * Used to crawl web content by a given URL.
 */
class WebCrawler
{
public:
	WebCrawler();
	~WebCrawler();

	string saveSourceCode(util::UrlTarget &target, util::TextBuffer &buff_);
	bool getContent(UrlTarget &url_, bool isHTTPS_);

private:
	std::string getContent(const std::string& strURL_, bool isHTTPS_, bool& _isError);
	std::string addPrefixAndSufixUrl(const std::string& url);
	vector<UrlTarget> _targets;
};

}} // namespace Mitrais::util



#endif /* INC_WEBCRAWLER_H_ */
