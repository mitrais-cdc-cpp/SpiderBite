/*
 * TextWriter.cpp
 *
 *  Created on: Jun 21, 2016
 *      Author: Andi_y
 */

#include "../inc/TextWriter.h"

namespace Mitrais {
	namespace util {

		std::ofstream fileStream;

		/**
		 * TextWriter default constructor
		 */
		TextWriter::TextWriter()
		{

		}

		/**
		 * TextWriter destructor
		 */
		TextWriter::~TextWriter()
		{

		}

		/**
		 * TextWriter constructor with param
		 *
		 * @params std::string filepath a filepath
		 */
		TextWriter::TextWriter(std::string filepath) :
				_file(filepath)
		{

		}

		/**
		 * TextWriter constructor with params
		 *
		 * @params std::string filepath a filepath
		 * @params std::string content a content
		 */
		TextWriter::TextWriter(std::string filepath, std::string content) :
				_file(filepath),
					_content(content)
		{

		}

		/**
		 * Set Content method
		 *
		 * @params std::string value a value
		 */
		void TextWriter::setContent(std::string value)
		{
			_content = value;
		}

		/**
		 * Set file path method
		 *
		 * @params std::string value a value
		 */
		void TextWriter::setFilePath(std::string value)
		{
			_file = value;
		}

		/**
		 * Write to file method
		 *
		 * @params BaseResponse& response a response
		 * @params bool isSaveAsHtml is save as HTML
		 */
		void TextWriter::writeToFile(BaseResponse& response, bool isSaveAsHtml)
		{
			try
			{
				std::string fileName = _file;
				if (isSaveAsHtml) {
					fileName = _file + ".html";
				}

				fileStream.open(fileName.c_str(), std::ios::trunc);

				if(fileStream.is_open())
				{
					// insert the content to file stream
					fileStream << _content;

					// close file stream after insert
					fileStream.close();

					response.updateStatus(true);
					response.addSuccessMessage();
				}
				else
				{
					response.addMessage("Unable to open " + _file);
					response.updateStatus(false);
				}
			}
			catch (std::exception& ex)
			{
				response.addMessage(ex.what());
				response.updateStatus(false);
			}
		}
	}
}


