/*
 * MainUI.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: adityo_w
 */

#include "../../inc/ui/MainUI.h"

namespace Mitrais
{
	namespace UI
	{
		GtkWidget *_start_btn;
		GtkWidget *_stop_btn;

		std::string _filePath;

		/**
		 * Default constructor of MainUI
		 */
		MainUI::MainUI()
		{
		}

		/**
		 * Destroyer of MainUI
		 */
		MainUI::~MainUI()
		{
		}

		/**
		 * convert std string to char pointer
		 * params str an std string
		 */
		char* convertStringToPChar(string str)
		{
			char *cstr = new char[str.length() + 1];
			strcpy(cstr, str.c_str());
			return cstr;
		}

		static void setButtonDisability()
		{
			if (_filePath.empty())
			{
				// enable start button
				gtk_widget_set_sensitive (_start_btn, FALSE);
				gtk_widget_set_sensitive (_stop_btn, FALSE);
			}
			else
			{
				gtk_widget_set_sensitive (_start_btn, TRUE);
				gtk_widget_set_sensitive (_stop_btn, FALSE);
			}
		}

		/**
		 * Callback method for start button
		 * params button a GtkWidget pointer
		 * params buffer a GtkTextBuffer pointer
		 */
		static void onStartClicked (GtkWidget *button, GtkTextBuffer *buffer)
		{
			string url;
			gchar* text;
			GtkTextIter ei;

			// disable start button
			gtk_widget_set_sensitive (button, FALSE);

			// check if the _filePath is empty or not
			if (_filePath.empty())
			{
				// enable start button
				gtk_widget_set_sensitive (button, TRUE);

				return;
			}

			util::TextReader reader(_filePath);
			util::BaseResponse response;
			vector<util::UrlTarget> targets = reader.getUrls(response);
			if (response.getStatus())
			{
				if (targets.size() > 0)
				{
					for(auto const& target: targets)
					{
						util::SocketConnection conn(target.Url);
						bool isOpen = conn.isSocketOpen();

						if (isOpen)
						{
							url = "Socket connection into "+ target.Url + " is open\n"+
									"----------------------------------------------------------------------------\n";

							// TODO : Azis
							// Call WebCrawler class and display the result into text box
						}
						else
						{
							url = "Socket connection into "+ target.Url + " is open\n"+
									"Skip " + target.Url +" this url target\n"+
									"----------------------------------------------------------------------------\n";
						}

						text = convertStringToPChar(url);
						gtk_text_buffer_get_end_iter(buffer, &ei);
						gtk_text_buffer_insert(buffer, &ei, text, -1);
					}
				}
				else
				{
					url = "There is no URL records on " + _filePath + " file\n";

					text = convertStringToPChar(url);
					gtk_text_buffer_get_end_iter(buffer, &ei);
					gtk_text_buffer_insert(buffer, &ei, text, -1);
				}
			}
			else
			{
				url = "Could not open " + _filePath + " file with the following error(s) : \n";

				text = convertStringToPChar(url);
				gtk_text_buffer_get_end_iter(buffer, &ei);
				gtk_text_buffer_insert(buffer, &ei, text, -1);

				for(auto const& message: response.getMessages())
				{
					url = message+"\n";

					text = convertStringToPChar(url);
					gtk_text_buffer_get_end_iter(buffer, &ei);
					gtk_text_buffer_insert(buffer, &ei, text, -1);
				}
			}

			// enable stop button
			gtk_widget_set_sensitive (_stop_btn, TRUE);
		}

		/**
		 * Callback method for stop button
		 * params button a GtkWidget pointer
		 * params buffer a GtkTextBuffer pointer
		 */
		static void onStopClicked (GtkWidget *button, GtkTextBuffer *buffer)
		{
		}

		/**
		 * Callback method for open menu
		 * params button a GtkWidget pointer
		 * params window a GtkWidget pointer
		 */
		static void onOpenClicked(GtkWidget *widget, GtkWidget *window)
		{
			GtkWidget *dialog;

			dialog = gtk_file_chooser_dialog_new ("Chose file..",
			     GTK_WINDOW(window),
			     GTK_FILE_CHOOSER_ACTION_OPEN,
			     GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			     GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
			     NULL);

		   if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
		   {
				char *filename;

				filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
				_filePath = string(filename);
				g_free (filename);
		   }

		   setButtonDisability();

		   gtk_widget_destroy (dialog);
		}

		/**
		 * Callback method for quit menu
		 * params widget a GtkWidget pointer
		 */
		static void onQuitClicked (GtkWidget *widget, gpointer data)
		{
			gtk_main_quit ();
		}

		/**
		 * Activates the UI
		 * params argc an integer
		 * params argv an array of chars pointer
		 */
		void MainUI::activateUI(int argc, char *argv[])
		{
			GtkWidget *window;
			GtkWidget *vbox;
			GtkWidget *hbtn_box;
			GtkWidget *text_view;
			GtkTextBuffer *buffer;
			GtkWidget *menubar;
			GtkWidget *filemenu;
			GtkWidget *file;
			GtkWidget *open;
			GtkWidget *quit;

			gtk_init (&argc, &argv);

			/* Create a Window. */
			window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
			gtk_window_set_title (GTK_WINDOW (window), "Spiderbite");

			/* Set a decent default size for the window. */
			gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
			g_signal_connect (G_OBJECT (window), "destroy",
							G_CALLBACK (onQuitClicked),
							NULL);

			vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
			gtk_container_add (GTK_CONTAINER (window), vbox);

			/* Create menubar and the menu list itself.*/
			menubar = gtk_menu_bar_new();
			filemenu = gtk_menu_new();
			file = gtk_menu_item_new_with_label("File");
			open = gtk_menu_item_new_with_label("Open");
			quit = gtk_menu_item_new_with_label("Quit");
			gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
			gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
			gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
			gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
			gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);

			//Connects GCallback function open_activated to "activate" signal for "open" menu item
			g_signal_connect(G_OBJECT(open), "activate", G_CALLBACK(onOpenClicked), window);
			//Connects GCallback function quit_activated to "activate" signal for "quit" menu item
			g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(onQuitClicked), NULL);

			/* Create a multiline text widget. */
			text_view = gtk_text_view_new ();
			gtk_text_view_set_editable (GTK_TEXT_VIEW (text_view), FALSE);
			gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (text_view), FALSE);
			gtk_box_pack_start (GTK_BOX (vbox), text_view, TRUE, TRUE, 0);

			/* Obtaining the buffer associated with the widget. */
			buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
			/* Set the default buffer text. */
			gtk_text_buffer_set_text (buffer, "", -1);

			/* Create a horizontal button box */
			hbtn_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
			gtk_button_box_set_layout (GTK_BUTTON_BOX(hbtn_box), GTK_BUTTONBOX_END);
			gtk_container_add (GTK_CONTAINER (vbox), hbtn_box);

			/* Create a start button. */
			_start_btn = gtk_button_new_with_label ("Start");
			gtk_box_pack_start (GTK_BOX (hbtn_box), _start_btn, TRUE, FALSE, 0);
			g_signal_connect (G_OBJECT (_start_btn), "clicked",
							G_CALLBACK (onStartClicked),
							buffer);

			/* Create a stop button. */
			_stop_btn = gtk_button_new_with_label ("Stop");
			gtk_box_pack_start (GTK_BOX (hbtn_box), _stop_btn, TRUE, FALSE, 0);
			g_signal_connect (G_OBJECT (_stop_btn), "clicked",
							G_CALLBACK (onStopClicked),
							buffer);

			setButtonDisability();

			gtk_widget_show_all (window);

			gtk_main ();
		}
	}
}
