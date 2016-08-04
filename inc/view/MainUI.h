/*
 * MainUI.h
 *
 *  Created on: Jun 15, 2016
 *      Author: adityo_w
 */

#ifndef INC_MAINUI_H_
#define INC_MAINUI_H_

#include <gtk/gtk.h>

#include "../util/TextReader.h"
#include "../util/TextBuffer.h"
#include "../util/SocketConnection.h"
#include "../util/TextWriter.h"
#include "../util/TextLexer.h"
#include "../util/WebCrawler.h"
#include "../util/Logger.h"
#include "../util/Configuration.h"

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

			private:
				/**
				 * Configuration file name
				 */
				const std::string _configFileName = "Config.xml";

				/**
				 * Method to check configuration file setting.
				 * If the configuration file is not exist this method will create \n
				 * the default configuration file.
				 */
				void checkConfigSetting();
		};
	}
} //namespace Mitrais::UI

#endif /* INC_MAINUI_H_ */
