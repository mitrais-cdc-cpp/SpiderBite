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

		TextWriter::TextWriter()
		{

		}

		TextWriter::~TextWriter()
		{

		}

		TextWriter::TextWriter(std::string filepath) :
				_file(filepath)
		{

		}

		TextWriter::TextWriter(std::string filepath, std::string content) :
				_file(filepath),
					_content(content)
		{

		}

		void TextWriter::setContent(std::string value)
		{
			_content = value;
		}

		void TextWriter::setFilePath(std::string value)
		{
			_file = value;
		}

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
					fileStream << _content;
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


