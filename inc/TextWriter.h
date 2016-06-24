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

using namespace std;

namespace Mitrais {
namespace util {

class TextWriter {

public:
	/**
	 * Set Content method
	 *
	 * @params std::string value a value
	 */
	void setContent(std::string value);

	/**
	 * Set file path method
	 *
	 * @params std::string value a value
	 */
	void setFilePath(std::string value);

	/**
	 * TextWriter default constructor
	 */
	TextWriter();

	/**
	 * TextWriter constructor with param
	 *
	 * @params std::string filepath a filepath
	 */
	TextWriter(std::string filepath);

	/**
	 * TextWriter constructor with params
	 *
	 * @params std::string filepath a filepath
	 * @params std::string content a content
	 */
	TextWriter(std::string filepath, std::string content);

	/**
	 * TextWriter destructor
	 */
	~TextWriter();

	/**
	 * Write to file method
	 *
	 * @params BaseResponse& response a response
	 * @params bool isSaveAsHtml is save as HTML
	 */
	void writeToFile(BaseResponse& response, bool isSaveAsHtml);

private:
	std::string _content;
	std::string _file;
};

}
}  // namespace Mitrais

#endif /* INC_TEXTWRITER_H_ */
