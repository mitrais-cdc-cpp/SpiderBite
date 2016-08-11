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
#include <string>

#include "../util/SaveModeEnum.h"
#include "../util/ConfigSettings.h"

namespace Mitrais {
namespace View {

	typedef std::function<void()> CallbackFunction;

	class SettingView
	{
	public:
		virtual ~SettingView();
		static SettingView* getInstance();

		//Public interface
		void OpenForm(util::ConfigSettings conf);
		void CloseForm();

		//SettingsView callback
		void onSaveClicked(CallbackFunction callback);
		void onCancelClicked(CallbackFunction callback);
		void onCloseClicked(CallbackFunction callback);
		void onOpenDialogClicked(CallbackFunction callback);


		/**
		 * set config
		 * @param logfilename
		 * @param pathtolocaldir
		 * @param deepness
		 * @param savemode
		 * @param dbHost
		 * @param dbPort
		 * @param dbName
		 */
		void setConfiguration(std::string& logfilename,
							std::string& pathtolocaldir,
							int deepness,
							Mitrais::util::SaveModeEnum savemode,
							std::string& dbHost,
							int& dbPort,
							std::string& dbName);
//		std::string getConnectionString();
		std::string getDbHost();
		int getDbPort();
		std::string getDbName();
		std::string getLogFileName();
		std::string getPathToLocalDir();
		int getCrawlingDeepness();
		Mitrais::util::SaveModeEnum getSaveMode();

		std::string getStringFromTBox(GtkWidget* tbox);
		int getIntFromTBox(GtkWidget* tbox);
		bool getBooleanFromSpinBtn(GtkWidget* spinBtn);
		void closeSettingView();
		void setConfiguration();

	private:

		//Arguments nested class
		class SettingViewArgs;
		std::shared_ptr<SettingViewArgs> _args;

		//private ctor
		SettingView(std::shared_ptr<SettingView::SettingViewArgs> args_);
		SettingView();

		//Singleton self
		static SettingView* _self;

		CallbackFunction whenSaveClicked;
		CallbackFunction whenCancelClicked;
		CallbackFunction whenOpenDialogClicked;
		CallbackFunction whenCloseClicked;

		//Signals from gtk+
		static void onSaveButtonClicked();
		static void onCancelButtonClicked();
		static void onOpenDialogButtonClicked();
		static void onQuitButtonClicked();

		//UI Helper
		void CreateGuiElements();
		void CreateMainForm();
		void CreateGrid();
		void ConnectSignals();
		void SetPropertyUIArgsToPropertyUI(bool isSaveInFolderActive);
		void OpenDialog();
		void Show();
		void Hide();
		void Quit();

		GtkWidget* form_MainForm;			//MainForm
		GtkWidget* grid;					//GridView

		//Textboxes
		GtkWidget* tb_LocalSavePath;
		GtkWidget* tb_LogFileName;
		GtkWidget* tb_DbHost;
		GtkWidget* tb_DbPort;
		GtkWidget* tb_DbName;

		GtkWidget* stb_CrawlingDepth;
		GtkWidget* switch_SaveInFolder;

		//labels
		GtkWidget* label_LogFileName;
		GtkWidget* label_CrawlingDepth;
		GtkWidget* label_SaveInFolder;
		GtkWidget* label_LocalSavePath;
		GtkWidget* label_DbHost;
		GtkWidget* label_DbPort;
		GtkWidget* label_DbName;

		//buttons
		GtkWidget* btn_SelectPath;
		GtkWidget* btn_Save;
		GtkWidget* btn_Cancel;


		//others
		bool _bIsCreated;

		friend class MainView;

	};
}} //namespace Mitrais::UI


#endif /* INC_UI_PROPERTYUI_H_ */
