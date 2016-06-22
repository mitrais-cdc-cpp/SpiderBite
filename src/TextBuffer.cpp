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
		TextBuffer::TextBuffer()
		{
		}

		TextBuffer::~TextBuffer()
		{
		}

		void TextBuffer::insertContentToBuffer(string str)
		{
			_stringBuffer.push_back(str);
		}

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
