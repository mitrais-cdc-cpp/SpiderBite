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
#include "../SocketConnection.h"

using namespace Mitrais;

namespace Mitrais
{
	namespace UI
	{
		class MainUI
		{
			public:
				MainUI();
				~MainUI();

				void activateUI(int argc, char *argv[]);
		};
	}
} //namespace Mitrais::UI

#endif /* INC_MAINUI_H_ */
