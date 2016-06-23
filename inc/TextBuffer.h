/*
 * TextBuffer.h
 *
 *  Created on: Jun 22, 2016
 *      Author: developer
 */

#ifndef INC_TEXTBUFFER_H_
#define INC_TEXTBUFFER_H_

#include <vector>
#include <iostream>

using namespace std;

namespace Mitrais
{
	namespace util
	{
		class TextBuffer
		{
			public:
				/**
				 * Default constructor of TextBuffer class
				 */
				TextBuffer();

				/**
				 * Default destroyer of TextBuffer class
				 */
				~TextBuffer();

				/**
				 * Insert the stored string to a buffer
				 *
				 * @str the stored text
				 */
				void insertContentToBuffer(string str);

				/**
				 * Get the full content of text which stored in the buffer
				 */
				string getFullContent();

			private:
				/**
				 * The iterator
				 */
				vector<string>::iterator it;

				/**
				 * The collection of string as a buffer
				 */
				vector<string> _stringBuffer;
		};
	}
} //namespace Mitrais::util



#endif /* INC_TEXTBUFFER_H_ */
