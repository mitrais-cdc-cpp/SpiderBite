/*
 * MainUI.h
 *
 *  Created on: Jun 15, 2016
 *      Author: adityo_w
 */

#ifndef INC_MAINUI_H_
#define INC_MAINUI_H_

#include <gtk/gtk.h>

#include "../TextReader.h"
#include "../TextBuffer.h"
#include "../SocketConnection.h"
#include "../TextWriter.h"
#include "../TextLexer.h"
#include "../WebCrawler.h"
#include "../Logger.h"
#include "../XMLHelper.h"

using namespace Mitrais;
using namespace Mitrais::util;

namespace Mitrais
{
	namespace UI
	{
		class MainUI
		{
			public:
			/**
			 * Default constructor of MainUI
			 */
			MainUI();

			/**
			 * Destroyer of MainUI
			 */
			~MainUI();

			/**
			 * Activates the UI
			 * params argc an integer
			 * params argv an array of chars pointer
			 */
			void activateUI(int argc, char *argv[]);

			/**
			 * convert std string to char pointer
			 * params str an std string
			 */
			char* convertStringToPChar(string str);
		};
	}
} //namespace Mitrais::UI

#endif /* INC_MAINUI_H_ */
