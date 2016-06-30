/*
 * WebCrawler.h
 *
 *  Created on: Jun 24, 2016
 *      Author: developer
 */

#ifndef INC_WEBCRAWLER_H_
#define INC_WEBCRAWLER_H_

#include <iostream>
#include <curl/curl.h>

#include "TextBuffer.h"
#include "Logger.h"

using namespace std;

namespace Mitrais{
namespace util{

class WebCrawler
{
public:
	WebCrawler();
	~WebCrawler();

	void getContent(const std::string& strURL_, std::string& result);

private:

	// Callback for cURL
	//static size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);
};

}} // namespace Mitrais::util



#endif /* INC_WEBCRAWLER_H_ */
