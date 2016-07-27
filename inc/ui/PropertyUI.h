/*
 * PropertyUI.h
 *
 *  Created on: Jul 11, 2016
 *      Author: Ari Suarkadipa
 */

#ifndef INC_UI_PROPERTYUI_H_
#define INC_UI_PROPERTYUI_H_

#include <gtk/gtk.h>
#include <sys/stat.h>
#include <string>

#include "../Logger.h"
#include "../XMLHelper.h"
#include "../ConfigSettings.h"
#include "../SaveModeEnum.h"

using namespace std;
using namespace Mitrais::util;

namespace Mitrais
{
	namespace UI
	{
		class PropertyUI
		{
		public:

			PropertyUI();
			~PropertyUI();

			void activateUI(int argc, char *argv[]);
		};
	}
} //namespace Mitrais::UI


#endif /* INC_UI_PROPERTYUI_H_ */
