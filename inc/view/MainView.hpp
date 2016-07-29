/*
 * MainView.hpp
 *
 *  Created on: Jul 26, 2016
 *      Author: developer
 */

#ifndef INC_VIEW_MAINVIEW_HPP_
#define INC_VIEW_MAINVIEW_HPP_

#include <gtk/gtk.h>
#include <functional>
#include <iostream>
#include "SettingView.hpp"
#include "../util/Logger.h"

namespace Mitrais
{
	namespace View
	{
		typedef std::function<void()> CallbackFunction;

		class MainView
		{
		public:
			~MainView();
			MainView(MainView const&) = delete;
			void operator=(MainView const&) = delete;

			static MainView* getInstance();

			void onSaveClicked(CallbackFunction callback);
			void onQuitClicked(CallbackFunction callback);
			void onOpenClicked(CallbackFunction callback);
			void onStopClicked(CallbackFunction callback);
			void onStartClicked(CallbackFunction callback);
			void onSettingViewClicked(CallbackFunction callback);

			static void saveClicked(GtkWidget *widget, GtkWidget *window);
			static void quitClicked(GtkWidget *widget, gpointer data);
			static void openClicked(GtkWidget *widget, GtkWidget *window);
			static void stopClicked(GtkWidget *button, GtkTextBuffer *buffer);
			static void startClicked(GtkWidget *button, GtkTextBuffer *buffer);
			static void settingClicked();

			void clearTextBox();
			void setButtonAndMenuDisability();
			void setStringToTextBox(std::string str);
			void appendStringToTextBox(std::string str);
			std::string getStringFromTextBuffer();
			inline std::string getFilename(){ return _fileName; }

			void build();
			void start();
			void openSettingView();
			void showOpenDialog();
			void showSaveDialog();
			void closeMainView();
			void stopCrawlingProcess();
			void disableControlsWhenStartClicked();
			void displayFileContent(std::vector<std::string> urls);
		private:
			MainView();
			GtkTextBuffer* getPTextBuffer(GtkWidget* widget);
			SettingView* _settingView;
			void setTextBuffer(std::string str);
			void setMessageToStatusbar(std::string message);
			void setTextViewEditability(bool isEditable);
			void setTextViewCursorVisibility(bool isVisible);
			void setWidgetEnablement(GtkWidget* widget, bool isEnable);

			GtkTextBuffer* _textBuffer;
			GtkWidget* _window;
			GtkWidget* _statusBar;
			GtkWidget* _txtBox;
			GtkWidget* _startBtn;
			GtkWidget* _stopBtn;
			GtkWidget* _save;

			std::string _fileName;

			static MainView* m_instance;

			CallbackFunction whenSaveClicked;
			CallbackFunction whenQuitClicked;
			CallbackFunction whenOpenClicked;
			CallbackFunction whenStopClicked;
			CallbackFunction whenStartClicked;
			CallbackFunction whenSettingClicked;
		};
	}
}

#endif /* INC_VIEW_MAINVIEW_HPP_ */
