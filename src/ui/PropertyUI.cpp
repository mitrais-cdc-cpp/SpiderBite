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
		GtkWidget* _entry_local_saved_webpath;
		const char *config_name = "Config.xml";
		GtkWidget* _entry_db_host;
		GtkWidget* _entry_db_port;
		GtkWidget* _entry_db_name;
		GtkWidget* _entry_log_filename;
		GtkWidget* _spin_depth_of_crawling;
		GtkWidget* _switch_save_in_folder;

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
		 * Convert integer to char
		 * @param number: The integer number
		 * @return the char pointer
		 */
		char* convertIntegerToPCharX(int number)
		{
			std::string str = std::to_string(number);
			char *cstr = convertStringToPCharX(str);
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

			dialog = gtk_file_chooser_dialog_new ("Select folder..",
				 GTK_WINDOW(window),
				 GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
				 ("_Cancel"), GTK_RESPONSE_CANCEL,
				 ("_Select"), GTK_RESPONSE_ACCEPT,
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
		   gtk_entry_set_text(GTK_ENTRY(_entry_local_saved_webpath), convertStringToPCharX(_filePathX));

		   gtk_widget_destroy (dialog);
		}

		/*
		 * isExist function to check if file is exist or not
		 * @param string filename
		 * @return bool status
		 */
		bool isExisting(string filename)
		{
			 struct stat buffer;
			 return (stat (filename.c_str(), &buffer) == 0);
		}

		/**
		 * LoadConfigToForm to collect all values from config file,
		 * set it to setting form when its loaded.
		 *
		 * @param config
		 */
		void loadConfigToForm(ConfigSettings &config)
		{
			// get all the properties value
			string db_host = config.dbHost;
			int db_port = config.dbPort;
			string db_name = config.dbName;
			string log_file_name = config.logFileName;
			int crawling_deepness = config.crawlingDeepness;
			SaveModeEnum save_target = config.saveTarget;
			string path_to_local_dir = config.pathToLocalDir;

			bool isActive;
			if (save_target == SAVE_TO_FILE)
			{
				isActive = true;
			} else
			{
				isActive = false;
			}

			// set to form
			gtk_entry_set_text(GTK_ENTRY(_entry_db_host), convertStringToPCharX(db_host));
			gtk_entry_set_text(GTK_ENTRY(_entry_db_port), convertIntegerToPCharX(db_port));
			gtk_entry_set_text(GTK_ENTRY(_entry_db_name), convertStringToPCharX(db_name));
			gtk_entry_set_text(GTK_ENTRY(_entry_log_filename), convertStringToPCharX(log_file_name));
			gtk_spin_button_set_value(GTK_SPIN_BUTTON(_spin_depth_of_crawling), crawling_deepness);
			gtk_switch_set_active(GTK_SWITCH(_switch_save_in_folder), isActive);
			gtk_entry_set_text(GTK_ENTRY(_entry_local_saved_webpath), convertStringToPCharX(path_to_local_dir));
		}

		/**
		 * loadXML to load configuration file for setting's form
		 *
		 * @param filename
		 */
		void loadXML(char *filename)
		{
			XMLHelper helper;
			ConfigSettings conf;

			bool isExist = isExisting(string(filename));
			if (isExist)
			{
				LOG_INFO << "Config loaded";
				helper.loadXML(conf, filename);
				loadConfigToForm(conf);
			} else {
				LOG_INFO << "Config not found";
			}
		}

		/**
		 * saveXML to save configuration file
		 *
		 */
		void saveXML(GtkWidget *window)
		{
			LOG_INFO << "Save config function called!";

			// get all values from setting form
			string db_host = gtk_entry_get_text(GTK_ENTRY(_entry_db_host));
			int db_port = atoi(gtk_entry_get_text(GTK_ENTRY(_entry_db_port)));
			string db_name = gtk_entry_get_text(GTK_ENTRY(_entry_db_name));
			string log_file_name = gtk_entry_get_text(GTK_ENTRY(_entry_log_filename));
			int crawling_deepness = gtk_spin_button_get_value(GTK_SPIN_BUTTON(_spin_depth_of_crawling));
			bool isActive = gtk_switch_get_active(GTK_SWITCH(_switch_save_in_folder));
			string path_to_local_dir = gtk_entry_get_text(GTK_ENTRY(_entry_local_saved_webpath));

			SaveModeEnum save_target;
			if (isActive)
			{
				save_target = SAVE_TO_FILE;
			} else
			{
				save_target = SAVE_TO_DB;
			}

// TODO: add validation
			if(db_host.empty() || log_file_name.empty() || path_to_local_dir.empty())
			{
				/**
				 * Obsolete!
				 * need to add validation instead of destroying the view
				 */
//				LOG_INFO << "Config file save failed!";
//
//				GtkWidget *dialog;
//				GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
//				dialog = gtk_message_dialog_new (GTK_WINDOW(window),
//				                                 flags,
//				                                 GTK_MESSAGE_ERROR,
//				                                 GTK_BUTTONS_CLOSE,
//				                                 NULL);
//				gtk_message_dialog_set_markup (GTK_MESSAGE_DIALOG (dialog),
//												"All fields should be filled!");
//				gtk_dialog_run (GTK_DIALOG (dialog));
//				gtk_widget_destroy (dialog);
			}
			else
			{
				ConfigSettings settings(db_host,
										db_port,
										db_name,
										log_file_name,
										crawling_deepness,
										save_target,
										path_to_local_dir);
				string filename = string(config_name);

				XMLHelper helper;
				helper.saveXML(settings, filename.c_str());

				gtk_widget_destroy(GTK_WIDGET(window));

				LOG_INFO << "Config file saved!";
			}
		}

		/**
		 * Callback method for save menu
		 * @params GtkWidget *widget a widget
		 * @params GtkWidget *window a window
		 */
		static void onSaveClicked(GtkWidget *widget, GtkWidget *window)
		{
			LOG_INFO << "Save Clicked";
			saveXML(window);
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
			GtkWidget *grid;
			GtkWidget *label_db_host;
			GtkWidget *label_db_port;
			GtkWidget *label_db_name;
			GtkWidget *label_log_file_name ;
			GtkWidget *label_depth_of_crawling;
			GtkWidget *label_save_in_folder;
			GtkWidget *label_local_saved_webpath;
			GtkWidget *button_select_path;
			GtkWidget *button_save;
			GtkWidget *button_cancel;

			//gint context_id;
			gtk_init (&argc, &argv);

			/* Create a Window. */
			window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
			gtk_window_set_title (GTK_WINDOW (window), "Settings");
			gtk_container_set_border_width (GTK_CONTAINER (window), 10);
			gtk_window_set_default_size (GTK_WINDOW (window), 300, 300);

			// set resizeable false
			gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

			// create new grid layout
			grid = gtk_grid_new();

			//Create label
			label_db_host = gtk_label_new("Database Host : ");
			label_db_port = gtk_label_new("Database Port : ");
			label_db_name = gtk_label_new("Database Name : ");
			label_log_file_name = gtk_label_new("Log file name : ");

			// depth of recursion of crawling
			label_depth_of_crawling = gtk_label_new("Crawling deepness : ");

			// switch for saving in files/folder structure or database
			label_save_in_folder = gtk_label_new("Save in folder? :" );

			// path for local saved websites
			label_local_saved_webpath = gtk_label_new("Local saved web path : ");

			//Create entryBox
			_entry_db_host = gtk_entry_new ();
			_entry_db_port = gtk_entry_new();
			_entry_db_name = gtk_entry_new();
			_entry_log_filename = gtk_entry_new ();
			_spin_depth_of_crawling = gtk_spin_button_new_with_range(1, 3, 1);
			_switch_save_in_folder = gtk_switch_new ();
			_entry_local_saved_webpath = gtk_entry_new ();

			//Create button to select the local saved website path
			button_select_path = gtk_button_new_with_label("...");

			/* Create a start button. */
			button_save = gtk_button_new_with_label ("Save");

			/* Create a stop button. */
			button_cancel = gtk_button_new_with_label ("Cancel");

			// attach the grids
			gtk_grid_attach(GTK_GRID(grid), label_db_host, 0, 15, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), _entry_db_host, 20, 15, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), label_db_port, 0, 30, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), _entry_db_port, 20, 30, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), label_db_name, 0, 45, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), _entry_db_name, 20, 45, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), label_log_file_name, 0, 60, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), _entry_log_filename, 20, 60, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), label_depth_of_crawling, 0, 75, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), _spin_depth_of_crawling, 20, 75, 10, 10);
			gtk_grid_attach(GTK_GRID(grid), label_save_in_folder, 0, 90, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), _switch_save_in_folder, 20, 90, 10, 10);
			gtk_grid_attach(GTK_GRID(grid), label_local_saved_webpath, 0, 105, 20, 10);
			gtk_grid_attach(GTK_GRID(grid), _entry_local_saved_webpath, 20, 105, 15, 10);
			gtk_grid_attach(GTK_GRID(grid), button_select_path, 37, 105, 10, 10);
			gtk_grid_attach(GTK_GRID(grid), button_save, 20, 120, 10, 10);
			gtk_grid_attach(GTK_GRID(grid), button_cancel, 30, 120, 10, 10);

			// set label to justify left
			gtk_label_set_xalign(GTK_LABEL(label_db_host), 0);
			gtk_label_set_xalign(GTK_LABEL(label_db_port), 0);
			gtk_label_set_xalign(GTK_LABEL(label_db_name), 0);
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
			g_signal_connect (GTK_ENTRY(_entry_db_host), "activate", G_CALLBACK(entry_activate), label_db_host);
			g_signal_connect (GTK_ENTRY(_entry_db_port), "activate", G_CALLBACK(entry_activate), label_db_port);
			g_signal_connect (GTK_ENTRY(_entry_db_name), "activate", G_CALLBACK(entry_activate), label_db_name);
			g_signal_connect (GTK_ENTRY(_entry_log_filename), "activate", G_CALLBACK(entry_activate), label_log_file_name);
			g_signal_connect (GTK_SPIN_BUTTON(_spin_depth_of_crawling), "activate", G_CALLBACK(entry_activate), label_depth_of_crawling);
			g_signal_connect (GTK_SWITCH(_switch_save_in_folder), "activate", G_CALLBACK(entry_activate), label_save_in_folder);
			g_signal_connect (GTK_ENTRY(_entry_local_saved_webpath), "activate", G_CALLBACK(entry_activate), label_local_saved_webpath);
			g_signal_connect (G_OBJECT(button_select_path), "clicked", G_CALLBACK(onOpenClicked), window);
			g_signal_connect (G_OBJECT (button_save), "clicked",G_CALLBACK (onSaveClicked), window);
			g_signal_connect (G_OBJECT (button_cancel), "clicked",G_CALLBACK (onQuitClicked), window);

			// add grid to window container
			gtk_container_add(GTK_CONTAINER(window), grid);

			// load configuration file
			loadXML((char*)config_name);

			gtk_widget_show_all (window);
			gtk_main ();
		}
	}
}


