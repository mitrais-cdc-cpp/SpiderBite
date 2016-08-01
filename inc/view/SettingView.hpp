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
		void OpenForm();
		void CloseForm();

		//getter/setter
		void setConfiguration(std::string& connection,std::string& logfilename,std::string& pathtolocaldir, int deepness, Mitrais::util::SaveModeEnum savemode);
		std::string getConnectionString();
		std::string getLogFileName();
		std::string getPathToLocalDir();
		int getCrawlingDeepness();
		Mitrais::util::SaveModeEnum getSaveMode();

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
		static void onSaveButtonClicked();
		static void onCancelButtonClicked();
		static void onOpenDialogClicked();
		static void onCloseForm();

		//UI Helper
		void CreateGuiElements();
		void CreateMainForm();
		void CreateGrid();
		void ConnectSignals();
		void SetPropertyUIArgsToPropertyUI(bool isSaveInFolderActive);
		void OpenDialog();
		void Show();
		void Quit();

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


		//others
		bool _bIsCreated;

		friend class MainView;

	};
}} //namespace Mitrais::UI


#endif /* INC_UI_PROPERTYUI_H_ */
