/*
 * PropertyUI.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: Ari Suarkadipa
 */
#include "../../inc/ui/PropertyUI.h"

namespace Mitrais
{
	namespace UI
	{
		string _filePathX;
		GtkWidget *_entryLocalSavedWebPath;

		/**
		 * Default constructor of MainUI
		 */
		PropertyUI::PropertyUI() { }

		/**
		 * Destroyer of MainUIl
		 */
		PropertyUI::~PropertyUI() { }

		/**
		 * Callback method for quit menu
		 * params widget a GtkWidget pointer
		 */
		static void onQuitClicked (GtkWidget *widget, gpointer window)
		{
			LOG_INFO << "Property terminated";
			gtk_widget_destroy(GTK_WIDGET(window));
		}

		/**
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
		 * convert std string to char pointer
		 * params str an std string
		 */
		char* convertStringToPCharX(string str)
		{
			char *cstr = new char[str.length() + 1];
			strcpy(cstr, str.c_str());
			return cstr;
		}

		/**
		 * Callback method for open menu
		 * params button a GtkWidget pointer
		 * params window a GtkWidget pointer
		 */
		static void onOpenClicked(GtkWidget *widget, GtkWidget *window)
		{
			LOG_INFO << "Open menu clicked";

			GtkWidget *dialog;

			dialog = gtk_file_chooser_dialog_new ("Chose file..",
				 GTK_WINDOW(window),
				 GTK_FILE_CHOOSER_ACTION_OPEN,
				 ("_Cancel"), GTK_RESPONSE_CANCEL,
				 ("_Open"), GTK_RESPONSE_ACCEPT,
				 NULL);

		   if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
		   {
				char *filename;

				filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
				_filePathX = string(filename);
				g_free (filename);

				LOG_INFO << "URL file loaded:" +_filePathX;
		   }

		   // show the file path in entry local saved web path
		   gtk_entry_set_text(GTK_ENTRY(_entryLocalSavedWebPath), convertStringToPCharX(_filePathX));

		   gtk_widget_destroy (dialog);
		}

		/**
		 * Activates the UI
		 * params argc an integer
		 * params argv an array of chars pointer
		 */
		void PropertyUI::activateUI(int argc, char *argv[])
		{
			LOG_INFO << "Property UI activated";
			GtkWidget *window;
			GtkWidget *menubar;
			GtkWidget *filemenu;
			GtkWidget *menu;
			GtkWidget *save;
			GtkWidget *open;
			GtkWidget *quit;
			GtkWidget *scrolled_window;
			GtkWidget *grid;
			GtkWidget *labelDBConnString;
			GtkWidget *labelLogFileName ;
			GtkWidget *labelDepthOfCrawling;
			GtkWidget *labelSaveInFolder;
			GtkWidget *labelLocalSavedWebPath;
			GtkWidget *entryDBConnString;
			GtkWidget *entryLogFileName;
			GtkWidget *spinDepthOfCrawling;
			GtkWidget *switchSaveInFolder;
			GtkWidget *buttonSelectPath;

			//gint context_id;
			gtk_init (&argc, &argv);

			/* Create a Window. */
			window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
			gtk_window_set_title (GTK_WINDOW (window), "Settings");
			gtk_container_set_border_width (GTK_CONTAINER (window), 10);
			gtk_window_set_default_size (GTK_WINDOW (window), 300, 200);

			grid = gtk_grid_new();

			/* Create menubar and the menu list itself.*/
			menubar = gtk_menu_bar_new();
			filemenu = gtk_menu_new();
			menu = gtk_menu_item_new_with_label("Menu");
			save = gtk_menu_item_new_with_label("Save");
			quit = gtk_menu_item_new_with_label("Quit");

			gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu), filemenu);
			gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu);
			gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
						gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);

			//Connects GCallback function quit_activated to "activate" signal for "quit" menu item
			g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(onQuitClicked), window);

			//Create label
			labelDBConnString = gtk_label_new("DB conn string : ");
			labelLogFileName = gtk_label_new("Log file name : ");

			// depth of recursion of crawling
			labelDepthOfCrawling = gtk_label_new("Depth crawling recursion : ");

			// switch for saving in files/folder structure or database
			labelSaveInFolder = gtk_label_new("Save in folder?" );

			// path for local saved websites
			labelLocalSavedWebPath = gtk_label_new("Local saved web path : ");

			//Create entryBox
			entryDBConnString = gtk_entry_new ();
			entryLogFileName = gtk_entry_new ();
			spinDepthOfCrawling = gtk_spin_button_new_with_range(1, 3, 1);
			switchSaveInFolder = gtk_switch_new ();
			_entryLocalSavedWebPath = gtk_entry_new ();

			//Create button to select the local saved website path
			buttonSelectPath = gtk_button_new_with_label("...");

			// attach the grids
			gtk_grid_attach(GTK_GRID(grid), menubar, 0, 0, 10, 10);
			gtk_grid_attach(GTK_GRID(grid), labelDBConnString, 0, 15, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), entryDBConnString, 20, 15, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), labelLogFileName, 0, 30, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), entryLogFileName, 20, 30, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), labelDepthOfCrawling, 0, 45, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), spinDepthOfCrawling, 20, 45, 10, 10);
			gtk_grid_attach(GTK_GRID(grid), labelSaveInFolder, 0, 60, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), switchSaveInFolder, 20, 60, 10, 10);
			gtk_grid_attach(GTK_GRID(grid), labelLocalSavedWebPath, 0, 75, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), _entryLocalSavedWebPath, 20, 75, 15, 10);
			gtk_grid_attach(GTK_GRID(grid), buttonSelectPath, 37, 75, 10, 10);

			// callbacks
			g_signal_connect (GTK_ENTRY(entryDBConnString), "activate", G_CALLBACK(entry_activate), labelDBConnString);
			g_signal_connect (GTK_ENTRY(entryLogFileName), "activate", G_CALLBACK(entry_activate), labelLogFileName);
			g_signal_connect (G_OBJECT(spinDepthOfCrawling), "activate", G_CALLBACK(entry_activate), labelDepthOfCrawling);
			g_signal_connect (GTK_ENTRY(switchSaveInFolder), "activate", G_CALLBACK(entry_activate), labelSaveInFolder);
			g_signal_connect (GTK_ENTRY(_entryLocalSavedWebPath), "activate", G_CALLBACK(entry_activate), labelLocalSavedWebPath);
			g_signal_connect (G_OBJECT(buttonSelectPath), "clicked", G_CALLBACK(onOpenClicked), window);

			// add grid to window container
			gtk_container_add(GTK_CONTAINER(window), grid);

			gtk_widget_show_all (window);
			gtk_main ();
		}
	}
}


