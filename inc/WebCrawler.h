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

#include "TextBuffer.h"
#include "Logger.h"
#include "UrlTarget.h"

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

	void getContent(const util::UrlTarget& strURL_, std::string& result);
	void getContent(const util::UrlTarget& strURL_, std::string& result_, bool isHTTPS_);

private:
	std::string addPrefixAndSufixUrl(const util::UrlTarget& url);
};

}} // namespace Mitrais::util



#endif /* INC_WEBCRAWLER_H_ */
