/**
 * $Id: $
 ******************************************************************************
 *  COPYRIGHT (C) 2016: MITRAIS – CONTINUOUS COMMITMENT, 80223 Bali
 * ---------------------------------------------------------------------------
 *  PROJECT:            SpiderBite
 *
 *  SOURCE FILE:        inc/TextReader.h
 *  TYPE:               Sourcefile
 *  COMPONENT:          Text Reader
 *  ---------------------------------------------------------------------------
 *
 *  BRIEF DESC:         This class propose to get a list of URLs in a text file.
 *  AUTHOR:             Fatoni, Mohammad Azis
 *  CREATION DATE:      06/14/2016
 *  LAST MODIFIED:      Date: 06/14/2016, Author: Fatoni, Mohammad Azis
 *
 *  LANGUAGE:           C/C++
 *  OPERATING SYSTEM:   Linux
 *  TARGET PROCESSOR:   i386
 *  GENERATOR:          none
 *  COMPILER:           gcc
 *
 *  REVISION INFO:
 *  -----------------------
 *  $Rev:  0.1
 *  $Date: 06/14/2016
 *  $URL:  inc/TextReader.h
 *
 *  PURPOSE:
 *  ---------------------
 *  This class propose to read a URL list from a trxt file
 *
 *  @remarks
 *  ERROR HANDLING:\n
 *    Error handling is done by Error-Code 12000 to 12500, ...
 *
 *    In normal case...
 *
 *  @remarks
 *  IMPLEMENTATION DETAILS:\n
 *	The following identifiers have to be set in constructor:
 *	- _filePath
 *
 *	Although  we set in constructor, we could set in setFilePath function.
 *
 *	After the file path is defined, the GetUrls function will read line by line and save into a vector of string
 *
 */

#ifndef SPIDERBITE_INC_TEXTREADER_H_
#define SPIDERBITE_INC_TEXTREADER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

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
	std::vector<std::string> getUrls(std::string filePath);

private:
	std::string _filePath;
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
