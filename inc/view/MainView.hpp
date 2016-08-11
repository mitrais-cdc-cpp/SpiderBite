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

			// MainView callback
			void onSaveClicked(CallbackFunction callback);
			void onQuitClicked(CallbackFunction callback);
			void onOpenClicked(CallbackFunction callback);
			void onStopClicked(CallbackFunction callback);
			void onStartClicked(CallbackFunction callback);
			void onSettingViewClicked(CallbackFunction callback);

			// MainView -> SettingsView callback
			void onSVSaveClicked(CallbackFunction callback);
			void onSVCancelClicked(CallbackFunction callback);
			void onSVCloseClicked(CallbackFunction callback);
			void onSVOpenDialogClicked(CallbackFunction callback);

			// SettingView callback
			void SaveConfiguration(CallbackFunction cb_SaveConfigurationClicked_);
			void QuitSettingClicked(CallbackFunction cb_OpenClicked_);
			void OpenSettingClicked(CallbackFunction cb_QuitClicked_);

			// MainView Events
			static void saveClicked(GtkWidget *widget, GtkWidget *window);
			static void quitClicked(GtkWidget *widget, gpointer data);
			static void openClicked(GtkWidget *widget, GtkWidget *window);
			static void stopClicked(GtkWidget *button, GtkTextBuffer *buffer);
			static void startClicked(GtkWidget *button, GtkTextBuffer *buffer);
			static void settingClicked();

			// SettingView Events
			static void onSaveConfigurationClicked(GtkWidget *widget, GtkWidget *window);
			static void onQuitSettingClicked(GtkWidget *widget, GtkWidget *window);
			static void onOpenSettingClicked(GtkWidget *widget, GtkWidget *window);

			void clearTextBox();
			void setButtonAndMenuDisability();
			void setStringToTextBox(std::string str);
			void appendStringToTextBox(std::string str);
			std::string getStringFromTextBuffer();
			inline std::string getFilename(){ return _fileName; }

			void build();
			void start();
			void openSettingView(util::ConfigSettings conf);
			void showOpenDialog();
			void showSaveDialog();
			void closeMainView();
			void stopCrawlingProcess();
			void disableControlsWhenStartClicked();
			void enableControlsWhenStopClicked();
			void displayFileContent(std::vector<std::string> urls);
			std::string getFileName();
			void setMessageToStatusbar(std::string message);

			//delegtes to SettingForm
			void onSettingFormCloseForm();
			void onSettingFormOpenDialogClicked();
			Mitrais::util::ConfigSettings onSettingFormSaveButtonClicked();
			void onSettingFormCancelButtonClicked();



		private:
			MainView();
			GtkTextBuffer* getPTextBuffer(GtkWidget* widget);
			SettingView* _settingView;
			void setTextBuffer(std::string str);
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

			//Callback function pointers
			CallbackFunction cb_SaveConfigurationClicked;
			CallbackFunction cb_OpenClicked;
			CallbackFunction cb_QuitClicked;
		};
	}
}

#endif /* INC_VIEW_MAINVIEW_HPP_ */
