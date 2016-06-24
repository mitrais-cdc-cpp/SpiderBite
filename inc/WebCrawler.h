/*
 * WebCrawler.h
 *
 *  Created on: Jun 24, 2016
 *      Author: developer
 */

#ifndef INC_WEBCRAWLER_H_
#define INC_WEBCRAWLER_H_

#include <iostream>
#include <urdl/read_stream.hpp>

#include "TextBuffer.h"

using namespace std;

namespace Mitrais{
namespace util{


class WebCrawler
{
public:
	WebCrawler();
	~WebCrawler();

	Mitrais::util::TextBuffer getContent(std::string strURL_);

private:
};

}} // namespace Mitrais::util



#endif /* INC_WEBCRAWLER_H_ */
