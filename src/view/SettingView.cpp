/*
 * PropertyUI.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: Ari Suarkadipa
 */
#include "../../inc/view/SettingView.hpp"

#include "../../inc/util/Logger.h"
#include "../../inc/util/SaveModeEnum.h"

using namespace Mitrais::View;

SettingView* SettingView::_self = nullptr;

class SettingView::SettingViewArgs
{
public:

	SettingViewArgs(std::string& logfilename,
					std::string& pathtolocaldir,
					int deepness,
					Mitrais::util::SaveModeEnum savemode,
					std::string& dbHost,
					int& dbPort,
					std::string& dbName)
	: _strLogFileName(logfilename)
	, _strPathToLocalDirectory(pathtolocaldir)
	, _iCrawlingDeepness(deepness)
	, _enumSaveMode(savemode)
	, _strDbHost(dbHost)
	, _iDbPort(dbPort)
	, _strDbName(dbName)
	{}

	SettingViewArgs()
	{}
	std::string 				_strLogFileName = "logfile.log";
	std::string 				_strPathToLocalDirectory = "./";
	int 						_iCrawlingDeepness = 1;
	Mitrais::util::SaveModeEnum _enumSaveMode = Mitrais::util::NOT_SET;
	std::string					_strDbHost = "";
	int							_iDbPort = 0;
	std::string					_strDbName = "";
};

SettingView::SettingView() : _args( new SettingView::SettingViewArgs() )
{
}

SettingView::~SettingView()
{
	gtk_widget_destroy(form_MainForm);
	delete _self;
}

void SettingView::closeSettingView()
{
	LOG_INFO << "Setting View closed";

}

SettingView* SettingView::getInstance()
{
	static SettingView* _self =  nullptr;

	if(!_self)
	{
		_self = new SettingView();
		//_args = ;
	}

	return _self;
}

std::string SettingView::getDbHost()
{
	return _args->_strDbHost;
}

int SettingView::getDbPort()
{
	return _args->_iDbPort;
}

std::string SettingView::getDbName()
{
	return _args->_strDbName;
}

std::string SettingView::getLogFileName()
{
	return _args->_strLogFileName;
}
std::string SettingView::getPathToLocalDir()
{
	return _args->_strPathToLocalDirectory;
}
int SettingView::getCrawlingDeepness()
{
	return _args->_iCrawlingDeepness;
}
Mitrais::util::SaveModeEnum SettingView::getSaveMode()
{
	return _args->_enumSaveMode;
}

/**
 * TODO: not done ref.
 *
 * Entry activate callback
 *
 * @param entry gtk entry
 * @param label gtk label
 */
static void entry_activate (GtkEntry *entry, GtkLabel *label)
{
	const char *entry_in = gtk_entry_get_text (entry);
	gtk_label_set_text (label, entry_in);
}

/**
 * LoadConfigToForm to collect all values from config file,
 * set it to setting form when its loaded.
 *
 * @param config
 */
void SettingView::setConfiguration(
					std::string& logfilename,
					std::string& pathtolocaldir,
					int deepness,
					Mitrais::util::SaveModeEnum savemode,
					std::string& dbHost,
					int& dbPort,
					std::string& dbName)
{
	_args->_strLogFileName = logfilename;
	_args->_strPathToLocalDirectory = pathtolocaldir;
	_args->_iCrawlingDeepness = deepness;
	_args->_enumSaveMode = savemode;
	_args->_strDbHost = dbHost;
	_args->_iDbPort = dbPort;
	_args->_strDbName = dbName;

	bool isActive = (savemode == Mitrais::util::SAVE_TO_FILE) ? true : false;

	SetPropertyUIArgsToPropertyUI(isActive);
}

void SettingView::onSaveClicked(CallbackFunction callback)
{
	whenSaveClicked = callback;
}
void SettingView::onCancelClicked(CallbackFunction callback)
{
	whenCancelClicked = callback;
}
void SettingView::onOpenDialogClicked(CallbackFunction callback)
{
	whenOpenDialogClicked = callback;
}
void SettingView::onCloseClicked(CallbackFunction callback)
{
	whenCloseClicked = callback;
}




void SettingView::onQuitButtonClicked()
{
	LOG_INFO << "onQuitClicked()";
	SettingView::getInstance()->whenCloseClicked();
}

void SettingView::onOpenDialogButtonClicked()
{
	LOG_INFO << "onSaveButtonClicked()";
	SettingView::getInstance()->whenOpenDialogClicked();
}

void SettingView::onSaveButtonClicked()
{
	LOG_INFO << "onSaveButtonClicked()";
	SettingView::getInstance()->whenSaveClicked();
}

void SettingView::onCancelButtonClicked()
{
	LOG_INFO << "onCancelButtonClicked()";
	SettingView::getInstance()->whenCancelClicked();
}




void SettingView::OpenForm(Mitrais::util::ConfigSettings conf)
{
	LOG_INFO << "Property UI activated";

	//gint context_id;

	if(!_bIsCreated)
	{
		//call my helpers
		CreateMainForm();
		CreateGuiElements();
		ConnectSignals();
		CreateGrid();
		setConfiguration(
				conf.logFileName,
				conf.pathToLocalDir,
				conf.crawlingDeepness,
				conf.saveTarget,
				conf.dbHost,
				conf.dbPort,
				conf.dbName);

		_bIsCreated = true;
	}

	// show myself
	Show();
}

void SettingView::CloseForm()
{
	Hide();
}

void SettingView::Show()
{
	gtk_widget_show_all(form_MainForm);
	gtk_main();
}

void SettingView::Hide()
{
	gtk_widget_hide(form_MainForm);
}

void SettingView::Quit()
{
	gtk_widget_destroy(GTK_WIDGET(form_MainForm));
}

void SettingView::ConnectSignals()
{
	// callbacks
//	g_signal_connect (GTK_ENTRY(tb_DbConnectionString), "activate", G_CALLBACK(entry_activate), label_DbConnectionString);
	g_signal_connect (GTK_ENTRY(tb_DbHost), "activate", G_CALLBACK(entry_activate), label_DbHost);
	g_signal_connect (GTK_ENTRY(tb_DbPort), "activate", G_CALLBACK(entry_activate), label_DbPort);
	g_signal_connect (GTK_ENTRY(tb_DbName), "activate", G_CALLBACK(entry_activate), label_DbName);
	g_signal_connect (GTK_ENTRY(tb_LogFileName), "activate", G_CALLBACK(entry_activate), label_LogFileName);
	g_signal_connect (GTK_ENTRY(tb_LocalSavePath), "activate", G_CALLBACK(entry_activate), label_LocalSavePath);

	g_signal_connect (GTK_SPIN_BUTTON(stb_CrawlingDepth), "activate", G_CALLBACK(entry_activate), label_CrawlingDepth);
	g_signal_connect (GTK_SWITCH(switch_SaveInFolder), "activate", G_CALLBACK(entry_activate), label_SaveInFolder);

	g_signal_connect (G_OBJECT (btn_Save), "clicked",G_CALLBACK(onSaveButtonClicked), form_MainForm);
	g_signal_connect (G_OBJECT (btn_SelectPath), "clicked", G_CALLBACK(onOpenDialogButtonClicked), form_MainForm);
	g_signal_connect (G_OBJECT (btn_Cancel), "clicked",G_CALLBACK (onCancelButtonClicked), form_MainForm);
}

void SettingView::CreateMainForm()
{
	form_MainForm	= gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (form_MainForm), "Settings");
	gtk_container_set_border_width (GTK_CONTAINER (form_MainForm), 10);
	gtk_window_set_default_size (GTK_WINDOW (form_MainForm), 300, 300);

	// set resizeable false
	gtk_window_set_resizable(GTK_WINDOW(form_MainForm), FALSE);
}

void SettingView::CreateGrid()
{
	grid = gtk_grid_new();

	// attach the grids
//	gtk_grid_attach(GTK_GRID(grid), label_DbConnectionString, 0, 15, 20, 10);
//	gtk_grid_attach(GTK_GRID(grid), tb_DbConnectionString, 20, 15, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), label_DbHost, 0, 15, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), tb_DbHost, 20, 15, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), label_DbPort, 0, 30, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), tb_DbPort, 20, 30, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), label_DbName, 0, 45, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), tb_DbName, 20, 45, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), label_LogFileName, 0, 60, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), tb_LogFileName, 20, 60, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), label_CrawlingDepth, 0, 75, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), stb_CrawlingDepth, 20, 75, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), label_SaveInFolder, 0, 90, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), switch_SaveInFolder, 20, 90, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), label_LocalSavePath, 0, 105, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), tb_LocalSavePath, 20, 105, 15, 10);
	gtk_grid_attach(GTK_GRID(grid), btn_SelectPath, 37, 105, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), btn_Save, 20, 120, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), btn_Cancel, 30, 120, 10, 10);

	// set spacing between row in grid
	gtk_grid_set_row_spacing(GTK_GRID(grid), 2);

	// set spacing between column in grid
	gtk_grid_set_column_spacing(GTK_GRID(grid), 2);

	// add grid to window container
	gtk_container_add(GTK_CONTAINER(form_MainForm), grid);
}

void SettingView::CreateGuiElements()
{
	//Create Textboxes
//	tb_DbConnectionString	= gtk_entry_new ();
	tb_DbHost = gtk_entry_new ();
	tb_DbPort = gtk_entry_new();
	tb_DbName = gtk_entry_new();
	tb_LogFileName 			= gtk_entry_new ();
	tb_LocalSavePath 		= gtk_entry_new ();

	// disable _entry_local_saved_webpath
	gtk_widget_set_sensitive (tb_LocalSavePath, FALSE);

	//Create others
	stb_CrawlingDepth 		= gtk_spin_button_new_with_range(1, 3, 1);
	switch_SaveInFolder 	= gtk_switch_new ();

	//Create buttons
	btn_SelectPath 	= gtk_button_new_with_label("...");
	btn_Save 		= gtk_button_new_with_label("Save");
	btn_Cancel 		= gtk_button_new_with_label("Cancel");

	//Create labels
//	label_DbConnectionString 	= gtk_label_new("Database location: ");
	label_DbHost = gtk_label_new("Database Host : ");
	label_DbPort = gtk_label_new("Database Port : ");
	label_DbName = gtk_label_new("Database Name : ");
	label_LogFileName 			= gtk_label_new("Logfile name: ");
	label_CrawlingDepth 		= gtk_label_new("Crawling deepness: ");
	label_SaveInFolder 			= gtk_label_new("Save in folder:" );
	label_LocalSavePath 		= gtk_label_new("Local saved web path : ");

	// set label to justify left
//	gtk_label_set_xalign(GTK_LABEL(label_DbConnectionString), 0);
	gtk_label_set_xalign(GTK_LABEL(label_DbHost), 0);
	gtk_label_set_xalign(GTK_LABEL(label_DbPort), 0);
	gtk_label_set_xalign(GTK_LABEL(label_DbName), 0);
	gtk_label_set_xalign(GTK_LABEL(label_LogFileName), 0);
	gtk_label_set_xalign(GTK_LABEL(label_CrawlingDepth), 0);
	gtk_label_set_xalign(GTK_LABEL(label_SaveInFolder), 0);
	gtk_label_set_xalign(GTK_LABEL(label_LocalSavePath), 0);

}

void SettingView::SetPropertyUIArgsToPropertyUI(bool isSaveInFolderActive)
{
//	gtk_entry_set_text(GTK_ENTRY(tb_DbConnectionString), _args->_strConnection.c_str());
	gtk_entry_set_text(GTK_ENTRY(tb_DbHost), _args->_strDbHost.c_str());
	gtk_entry_set_text(GTK_ENTRY(tb_DbPort), std::to_string(_args->_iDbPort).c_str());
	gtk_entry_set_text(GTK_ENTRY(tb_DbName), _args->_strDbName.c_str());
	gtk_entry_set_text(GTK_ENTRY(tb_LogFileName), _args->_strLogFileName.c_str());
	gtk_entry_set_text(GTK_ENTRY(tb_LocalSavePath), _args->_strPathToLocalDirectory.c_str());
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(stb_CrawlingDepth), _args->_iCrawlingDeepness);
	gtk_switch_set_active(GTK_SWITCH(switch_SaveInFolder), isSaveInFolderActive);
}

void SettingView::OpenDialog()
{
	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new ( "Select folder..", GTK_WINDOW(form_MainForm),
											GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
											 ("_Cancel"), GTK_RESPONSE_CANCEL,
											 ("_Select"), GTK_RESPONSE_ACCEPT,
											 NULL );

   if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
   {
	  _args->_strPathToLocalDirectory = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
   }

   gtk_entry_set_text(GTK_ENTRY(tb_LocalSavePath), _args->_strPathToLocalDirectory.c_str());
   gtk_widget_destroy (dialog);
}

std::string SettingView::getStringFromTBox(GtkWidget* tbox)
{
	return gtk_entry_get_text(GTK_ENTRY(tbox));
}

int SettingView::getIntFromTBox(GtkWidget* tbox)
{
	return atoi(gtk_entry_get_text(GTK_ENTRY(tbox)));
}

bool SettingView::getBooleanFromSpinBtn(GtkWidget* spinBtn)
{
	return gtk_switch_get_active(GTK_SWITCH(spinBtn));
}

void SettingView::setConfiguration()
{
	std::string dbHost = getStringFromTBox(tb_DbHost);
	int dbPort = getIntFromTBox(tb_DbPort);
	std::string dbName = getStringFromTBox(tb_DbName);
	std::string logFileName = getStringFromTBox(tb_LogFileName);
	int crawlingDepth = getIntFromTBox(stb_CrawlingDepth);
	bool isSaveInFolder = getBooleanFromSpinBtn(switch_SaveInFolder);
	std::string localSavePath = getStringFromTBox(tb_LocalSavePath);

	Mitrais::util::SaveModeEnum saveEnum;
	if (isSaveInFolder)
	{
		saveEnum = Mitrais::util::SAVE_TO_FILE;
	} else
	{
		saveEnum = Mitrais::util::SAVE_TO_DB;
	}

	_args->_strLogFileName = logFileName;
	_args->_strPathToLocalDirectory = localSavePath;
	_args->_iCrawlingDeepness = crawlingDepth;
	_args->_enumSaveMode = saveEnum;
	_args->_strDbHost = dbHost;
	_args->_iDbPort = dbPort;
	_args->_strDbName = dbName;

	Hide();
}
