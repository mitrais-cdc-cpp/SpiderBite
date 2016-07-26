/*
 * TextBoxUI.h
 *
 *  Created on: Jun 17, 2016
 *      Author: developer
 */

#ifndef INC_UI_TEXTBOXUI_H_
#define INC_UI_TEXTBOXUI_H_

#include <gtk/gtk.h>

namespace Mitrais
{
	namespace UI
	{
		class TextBoxUI
		{
			public:
				TextBoxUI();
				~TextBoxUI();

				void initialize();
				GtkWidget* getGTKTextBox() const;
				void setText();

			private:

				GtkWidget 		*view;
				GtkTextBuffer 	*buffer;

				GtkTextIter 	iter;
		};
	}
} //namespace Mitrais::UI



#endif /* INC_UI_TEXTBOXUI_H_ */
