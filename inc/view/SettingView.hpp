/*
 * SettingView.hpp
 *
 *  Created on: Jul 26, 2016
 *      Author: developer
 */

#ifndef INC_VIEW_SETTINGVIEW_HPP_
#define INC_VIEW_SETTINGVIEW_HPP_

#include <gtk/gtk.h>
#include <functional>
#include <iostream>

namespace Mitrais
{
	namespace View
	{
		typedef std::function<void()> CallbackFunction;

		class SettingView
		{
		public:
			~SettingView();
			SettingView(SettingView const&) = delete;
			void operator=(SettingView const&) = delete;

			static SettingView* getInstance();

			void onQuitClicked(CallbackFunction callback);
			void onOpenClicked(CallbackFunction callback);
			void onSaveClicked(CallbackFunction callback);
			void onEntryKeyIn(CallbackFunction callback);

			static void quitClicked (GtkWidget *widget, gpointer window);
			static void openClicked(GtkWidget *widget, GtkWidget *window);
			static void saveClicked(GtkWidget *widget, GtkWidget *window);
			static void entryKeyIn(GtkEntry *entry, GtkLabel *label);

			void build();
			void start();
		private:
			SettingView();
			static SettingView* m_instance;

			CallbackFunction whenQuitClicked;
			CallbackFunction whenOpenClicked;
			CallbackFunction whenSaveClicked;
			CallbackFunction whenEntryKeyIn;
		};
	}
}


#endif /* INC_VIEW_SETTINGVIEW_HPP_ */
