/*
 * TextWriter.h
 *
 *  Created on: Jun 21, 2016
 *      Author: Andi_y
 */

#ifndef INC_TEXTWRITER_H_
#define INC_TEXTWRITER_H_

#include <iostream>
#include <fstream>
#include "BaseResponse.h"
#include <sys/stat.h>

using namespace std;

namespace Mitrais {
namespace util {

class TextWriter {

public:
	void setContent(std::string value);
	void setFilePath(std::string value);
	TextWriter();
	TextWriter(std::string filepath);
	TextWriter(std::string filepath, std::string content);
	~TextWriter();
	void writeToFile(BaseResponse& response);
	void writeAsHtmlFile(BaseResponse& response);

private:
	std::string _content;
	std::string _file;
	bool isFileExist();

};

}
}  // namespace Mitrais

#endif /* INC_TEXTWRITER_H_ */
