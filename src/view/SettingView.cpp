/*
 * SettingView.cpp
 *
 *  Created on: Jul 26, 2016
 *      Author: developer
 */

#include "../../inc/view/SettingView.hpp"

using namespace Mitrais::View;

SettingView* SettingView::m_instance = nullptr;

SettingView::SettingView()
{}

SettingView::~SettingView()
{
	delete m_instance;
}

SettingView* SettingView::getInstance()
{
	if(!m_instance)
		m_instance = new SettingView();

	return m_instance;
}

void SettingView::onQuitClicked(CallbackFunction callback)
{
	whenQuitClicked = callback;
}

void SettingView::onOpenClicked(CallbackFunction callback)
{
	whenOpenClicked = callback;
}

void SettingView::onSaveClicked(CallbackFunction callback)
{
	whenSaveClicked = callback;
}

void SettingView::onEntryKeyIn(CallbackFunction callback)
{
	whenEntryKeyIn = callback;
}

void SettingView::quitClicked (GtkWidget *widget, gpointer window)
{
	SettingView::getInstance()->whenQuitClicked();
}

void SettingView::openClicked(GtkWidget *widget, GtkWidget *window)
{
	SettingView::getInstance()->whenOpenClicked();
}

void SettingView::saveClicked(GtkWidget* widget, GtkWidget* window)
{
	SettingView::getInstance()->whenSaveClicked();
}

void SettingView::entryKeyIn(GtkEntry *entry, GtkLabel *label)
{
	SettingView::getInstance()->whenEntryKeyIn();
}

void SettingView::build()
{
	/* Create a Window. */
	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Settings");
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_window_set_default_size (GTK_WINDOW (window), 300, 170);

	// set resizeable false
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	// create new grid layout
	GtkWidget *grid = gtk_grid_new();

	//Create label
	GtkWidget *label_db_conn_string = gtk_label_new("Database location : ");
	GtkWidget *label_log_file_name = gtk_label_new("Log file name : ");

	// depth of recursion of crawling
	GtkWidget *label_depth_of_crawling = gtk_label_new("Crawling deepness : ");

	// switch for saving in files/folder structure or database
	GtkWidget *label_save_in_folder = gtk_label_new("Save in folder? :" );

	// path for local saved websites
	GtkWidget *label_local_saved_webpath = gtk_label_new("Local saved web path : ");

	//Create entryBox
	GtkWidget *_entry_db_conn_string = gtk_entry_new ();
	GtkWidget *_entry_log_filename = gtk_entry_new ();
	GtkWidget *_spin_depth_of_crawling = gtk_spin_button_new_with_range(1, 3, 1);
	GtkWidget *_switch_save_in_folder = gtk_switch_new ();
	GtkWidget *_entry_local_saved_webpath = gtk_entry_new ();

	//Create button to select the local saved website path
	GtkWidget *button_select_path = gtk_button_new_with_label("...");

	/* Create a save button. */
	GtkWidget *button_save = gtk_button_new_with_label ("Save");

	/* Create a cancel button. */
	GtkWidget *button_cancel = gtk_button_new_with_label ("Cancel");

	// attach the grids
	gtk_grid_attach(GTK_GRID(grid), label_db_conn_string, 0, 15, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), _entry_db_conn_string, 20, 15, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), label_log_file_name, 0, 30, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), _entry_log_filename, 20, 30, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), label_depth_of_crawling, 0, 45, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), _spin_depth_of_crawling, 20, 45, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), label_save_in_folder, 0, 60, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), _switch_save_in_folder, 20, 60, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), label_local_saved_webpath, 0, 75, 20, 10);
	gtk_grid_attach(GTK_GRID(grid), _entry_local_saved_webpath, 20, 75, 15, 10);
	gtk_grid_attach(GTK_GRID(grid), button_select_path, 37, 75, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), button_save, 20, 90, 10, 10);
	gtk_grid_attach(GTK_GRID(grid), button_cancel, 30, 90, 10, 10);

	// set label to justify left
	gtk_label_set_xalign(GTK_LABEL(label_db_conn_string), 0);
	gtk_label_set_xalign(GTK_LABEL(label_log_file_name), 0);
	gtk_label_set_xalign(GTK_LABEL(label_depth_of_crawling), 0);
	gtk_label_set_xalign(GTK_LABEL(label_save_in_folder), 0);
	gtk_label_set_xalign(GTK_LABEL(label_local_saved_webpath), 0);

	// disable _entry_local_saved_webpath
	gtk_widget_set_sensitive (_entry_local_saved_webpath, FALSE);

	// set spacing between row in grid
	gtk_grid_set_row_spacing(GTK_GRID(grid), 2);

	// set spacing between column in grid
	gtk_grid_set_column_spacing(GTK_GRID(grid), 2);

	// callbacks
	g_signal_connect (GTK_ENTRY(_entry_db_conn_string), "activate", G_CALLBACK(entryKeyIn), label_db_conn_string);
	g_signal_connect (GTK_ENTRY(_entry_log_filename), "activate", G_CALLBACK(entryKeyIn), label_log_file_name);
	g_signal_connect (GTK_SPIN_BUTTON(_spin_depth_of_crawling), "activate", G_CALLBACK(entryKeyIn), label_depth_of_crawling);
	g_signal_connect (GTK_SWITCH(_switch_save_in_folder), "activate", G_CALLBACK(entryKeyIn), label_save_in_folder);
	g_signal_connect (GTK_ENTRY(_entry_local_saved_webpath), "activate", G_CALLBACK(entryKeyIn), label_local_saved_webpath);
	g_signal_connect (G_OBJECT(button_select_path), "clicked", G_CALLBACK(openClicked), window);
	g_signal_connect (G_OBJECT (button_save), "clicked",G_CALLBACK (saveClicked), window);
	g_signal_connect (G_OBJECT (button_cancel), "clicked",G_CALLBACK (quitClicked), window);

	// add grid to window container
	gtk_container_add(GTK_CONTAINER(window), grid);

	// load configuration file
//	loadXML((char*)config_name);
}

void SettingView::start()
{
	gtk_main();
}
