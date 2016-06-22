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

				TextBuffer();
				~TextBuffer();

				void insertContentToBuffer(string str);
				string getFullContent();

			private:
				vector<string>::iterator it;
				vector<string> _stringBuffer;
		};
	}
} //namespace Mitrais::util



#endif /* INC_TEXTBUFFER_H_ */
