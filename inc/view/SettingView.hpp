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
#include <functional>
#include <memory>

#include "../util/SaveModeEnum.h"

namespace Mitrais {
namespace View {

	typedef std::function<void()> CallbackFunction;

	class SettingView
	{
	public:
		virtual ~SettingView();
		static SettingView* getInstance();

		//Public interface
		void quit();
		void show();
		void activateUI();

		//getter/setter
		void setConfiguration(std::string& connection,std::string& logfilename,std::string& pathtolocaldir, int deepness, Mitrais::util::SaveModeEnum savemode);
		std::string getConnectionString();
		std::string getLogFileName();
		std::string getPathToLocalDir();
		int getCrawlingDeepness();
		Mitrais::util::SaveModeEnum getSaveMode();

		//Events to register
		void SaveConfiguration(CallbackFunction cb_SaveConfigurationClicked_);
		void QuitClicked(CallbackFunction cb_OpenClicked_);
		void OpenClicked(CallbackFunction cb_QuitClicked_);


	private:

		//Arguments nested class
		class SettingViewArgs;
		std::shared_ptr<SettingViewArgs> _args;

		//private ctor
		SettingView(std::shared_ptr<SettingView::SettingViewArgs> args_);
		SettingView();

		//Singleton self
		static SettingView* _self;

		//Signals from gtk+
		static void onSaveConfigurationClicked();
		static void onQuitClicked();
		static void onOpenClicked();

		//UI Helper
		void CreateGuiElements();
		void CreateMainForm();
		void CreateGrid();
		void ConnectSignals();
		void SetPropertyUIArgsToPropertyUI(bool isSaveInFolderActive);
		void OpenDialog();

		GtkWidget* form_MainForm;			//MainForm
		GtkWidget* grid;					//GridView

		//Textboxes
		GtkWidget* tb_LocalSavePath;
		GtkWidget* tb_DbConnectionString;
		GtkWidget* tb_LogFileName;

		GtkWidget* stb_CrawlingDepth;
		GtkWidget* switch_SaveInFolder;

		//labels
		GtkWidget* label_DbConnectionString;
		GtkWidget* label_LogFileName;
		GtkWidget* label_CrawlingDepth;
		GtkWidget* label_SaveInFolder;
		GtkWidget* label_LocalSavePath;

		//buttons
		GtkWidget* btn_SelectPath;
		GtkWidget* btn_Save;
		GtkWidget* btn_Cancel;

		//Callback function pointers
		CallbackFunction cb_SaveConfigurationClicked;
		CallbackFunction cb_OpenClicked;
		CallbackFunction cb_QuitClicked;
	};
}} //namespace Mitrais::UI


#endif /* INC_UI_PROPERTYUI_H_ */
