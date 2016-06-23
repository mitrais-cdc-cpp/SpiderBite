/*
 * TextBuffer.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: developer
 */

#include "../inc/TextBuffer.h"

namespace Mitrais
{
	namespace util
	{
		/**
		 * Default constructor of TextBuffer class
		 */
		TextBuffer::TextBuffer()
		{
		}

		/**
		 * Default destroyer of TextBuffer class
		 */
		TextBuffer::~TextBuffer()
		{
		}

		/**
		 * Constructor of TextBuffer class
		 *
		 * @buffer The string buffer
		 */
		TextBuffer::TextBuffer(vector<string> buffer) :
				_stringBuffer(buffer)
		{
		}

		/**
		 * Insert the stored string to a buffer
		 *
		 * @str the stored text
		 */
		void TextBuffer::insertContentToBuffer(string str)
		{
			_stringBuffer.push_back(str);
		}

		/**
		 * Get the full content of text which stored in the buffer
		 */
		string TextBuffer::getFullContent()
		{
			string content;
			for(it=_stringBuffer.begin(); it<_stringBuffer.end(); it++)
			{
				content.append(*it);
			}

			return content;
		}
	}
}
