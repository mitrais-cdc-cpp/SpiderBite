/*
 * PropertyUI.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: Ari Suarkadipa
 */
#include "../../inc/view/SettingView.hpp"

#include "../../inc/util/Logger.h"
#include "../../inc/util/SaveModeEnum.h"

using namespace Mitrais::UI;




class SettingView::SettingViewArgs
{
public:

	SettingViewArgs(std::string& connection,
					std::string& logfilename,
					std::string& pathtolocaldir,
					int deepness,
					Mitrais::util::SaveModeEnum savemode)
	: _strConnection(connection)
	, _strLogFileName(logfilename)
	, _strPathToLocalDirectory(pathtolocaldir)
	, _iCrawlingDeepness(deepness)
	, _enumSaveMode(savemode)
	{}

	SettingViewArgs()
	{}

	std::string 				_strConnection = "";
	std::string 				_strLogFileName = "logfile.log";
	std::string 				_strPathToLocalDirectory = "./";
	int 						_iCrawlingDeepness = 1;
	Mitrais::util::SaveModeEnum _enumSaveMode = Mitrais::util::NOT_SET;
};


SettingView::SettingView()
{
}
SettingView::~SettingView()
{
}

SettingView* SettingView::getInstance()
{
	static SettingView* _self =  nullptr;

	if(!_self)
	{
		_self = new SettingView();
		//_args = std::make_shared<PropertyUIArgs>( new PropertyUIArgs() );
	}

	return _self;
}


std::string SettingView::getConnectionString()
{
	return _args->_strConnection;
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
void SettingView::setConfiguration(std::string& connection,
					std::string& logfilename,
					std::string& pathtolocaldir,
					int deepness,
					Mitrais::util::SaveModeEnum savemode)
{
	_args->_strConnection = connection;
	_args->_strLogFileName = logfilename;
	_args->_strPathToLocalDirectory = pathtolocaldir;
	_args->_iCrawlingDeepness = deepness;
	_args->_enumSaveMode = savemode;

	bool isActive = (savemode == Mitrais::util::SAVE_TO_FILE) ? true : false;

	SetPropertyUIArgsToPropertyUI(isActive);
}


void SettingView::SaveConfiguration(CallbackFunction cb_SaveConfigurationClicked_)
{
	cb_SaveConfigurationClicked = cb_SaveConfigurationClicked_;
}

void SettingView::OpenClicked(CallbackFunction cb_OpenClicked_)
{
	cb_OpenClicked = cb_OpenClicked_;
}

void SettingView::QuitClicked(CallbackFunction cb_QuitClicked_)
{
	cb_QuitClicked = cb_QuitClicked_;
}

void SettingView::onSaveConfigurationClicked()
{
	LOG_INFO << "onSaveConfigurationClicked()";
	SettingView::getInstance()->cb_SaveConfigurationClicked();
}

void SettingView::onQuitClicked ()
{
	LOG_INFO << "onQuitClicked()";
	SettingView::getInstance()->cb_QuitClicked();
}

void SettingView::onOpenClicked()
{
	LOG_INFO << "onOpenClicked()";
	SettingView::getInstance()->cb_OpenClicked();
}

/**
 * Activates the UI
 * params argc an integer
 * params argv an array of chars pointer
 */
void SettingView::activateUI(int argc, char *argv[])
{
	LOG_INFO << "Property UI activated";

	//gint context_id;
	gtk_init (&argc, &argv);

	//call my helpers
	CreateMainForm();
	CreateGuiElements();
	ConnectSignals();
	CreateGrid();

	// show myself
	show();
}

void SettingView::show()
{
	gtk_widget_show_all(form_MainForm);
	gtk_main();
}

void SettingView::quit()
{
	gtk_widget_destroy(GTK_WIDGET(form_MainForm));
}

void SettingView::ConnectSignals()
{
	// callbacks
	g_signal_connect (GTK_ENTRY(tb_DbConnectionString), "activate", G_CALLBACK(entry_activate), label_DbConnectionString);
	g_signal_connect (GTK_ENTRY(tb_LogFileName), "activate", G_CALLBACK(entry_activate), label_LogFileName);
	g_signal_connect (GTK_ENTRY(tb_LocalSavePath), "activate", G_CALLBACK(entry_activate), label_LocalSavePath);

	g_signal_connect (GTK_SPIN_BUTTON(stb_CrawlingDepth), "activate", G_CALLBACK(entry_activate), label_CrawlingDepth);
	g_signal_connect (GTK_SWITCH(switch_SaveInFolder), "activate", G_CALLBACK(entry_activate), label_SaveInFolder);

	g_signal_connect (G_OBJECT (btn_Save), "clicked",G_CALLBACK(SettingView::onSaveConfigurationClicked), form_MainForm);
	g_signal_connect (G_OBJECT (btn_SelectPath), "clicked", G_CALLBACK(SettingView::onOpenClicked), form_MainForm);
	g_signal_connect (G_OBJECT (btn_Cancel), "clicked",G_CALLBACK (SettingView::onQuitClicked), form_MainForm);

}


void SettingView::CreateMainForm()
{
	form_MainForm	= gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (form_MainForm), "Settings");
	gtk_container_set_border_width (GTK_CONTAINER (form_MainForm), 10);
	gtk_window_set_default_size (GTK_WINDOW (form_MainForm), 300, 170);

	// set resizeable false
	gtk_window_set_resizable(GTK_WINDOW(form_MainForm), FALSE);
}


void SettingView::CreateGrid()
{
	grid = gtk_grid_new();

	// attach the grids
	gtk_grid_attach(GTK_GRID(grid), label_DbConnectionString, 0, 15, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), tb_DbConnectionString, 20, 15, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), label_LogFileName, 0, 30, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), tb_LogFileName, 20, 30, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), label_CrawlingDepth, 0, 45, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), stb_CrawlingDepth, 20, 45, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), label_SaveInFolder, 0, 60, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), switch_SaveInFolder, 20, 60, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), label_LocalSavePath, 0, 75, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), tb_LocalSavePath, 20, 75, 15, 10);
	gtk_grid_attach(GTK_GRID(grid), btn_SelectPath, 37, 75, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), btn_Save, 20, 90, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), btn_Cancel, 30, 90, 10, 10);

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
	tb_DbConnectionString	= gtk_entry_new ();
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
	label_DbConnectionString 	= gtk_label_new("Database location: ");
	label_LogFileName 			= gtk_label_new("Logfile name: ");
	label_CrawlingDepth 		= gtk_label_new("Crawling deepness: ");
	label_SaveInFolder 			= gtk_label_new("Save in folder:" );
	label_LocalSavePath 		= gtk_label_new("Local saved web path : ");

	// set label to justify left
	gtk_label_set_xalign(GTK_LABEL(label_DbConnectionString), 0);
	gtk_label_set_xalign(GTK_LABEL(label_LogFileName), 0);
	gtk_label_set_xalign(GTK_LABEL(label_CrawlingDepth), 0);
	gtk_label_set_xalign(GTK_LABEL(label_SaveInFolder), 0);
	gtk_label_set_xalign(GTK_LABEL(label_LocalSavePath), 0);

}

void SettingView::SetPropertyUIArgsToPropertyUI(bool isSaveInFolderActive)
{
	gtk_entry_set_text(GTK_ENTRY(tb_DbConnectionString), _args->_strConnection.c_str());
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
	   _args->_strPathToLocalDirectory = std::string(gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog)));

   gtk_entry_set_text(GTK_ENTRY(tb_LocalSavePath), _args->_strPathToLocalDirectory.c_str());
   gtk_widget_destroy (dialog);
}

