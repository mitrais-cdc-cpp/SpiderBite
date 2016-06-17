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
		 * Callback method for start button
		 * params button a GtkWidget pointer
		 * params buffer a GtkTextBuffer pointer
		 */
		static void onStartClicked (GtkWidget *button, GtkTextBuffer *buffer)
		{
			GtkTextIter ei;

			gtk_text_buffer_get_end_iter(buffer, &ei);
			gtk_text_buffer_insert(buffer, &ei, "basdbasbdapod", -1);
		}

		/**
		 * Callback method for stop button
		 * params button a GtkWidget pointer
		 * params buffer a GtkTextBuffer pointer
		 */
		static void onStopClicked (GtkWidget *button, GtkTextBuffer *buffer)
		{
			g_print("Stop activated.\n");
		}

		/**
		 * Callback method for open menu
		 * params button a GtkWidget pointer
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
			    g_print(filename);
			    g_free (filename);
			   }

			   gtk_widget_destroy (dialog);
		}

		/**
		 * Callback method for quit menu
		 * params widget a GtkWidget pointer
		 */
		static void onQuitClicked (GtkWidget *widget)
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
			GtkWidget *start_btn;
			GtkWidget *stop_btn;
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
			gtk_text_buffer_set_text (buffer, "22Hello!", -1);

			/* Create a horizontal button box */
			hbtn_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
			gtk_button_box_set_layout (GTK_BUTTON_BOX(hbtn_box), GTK_BUTTONBOX_END);
			gtk_container_add (GTK_CONTAINER (vbox), hbtn_box);

			/* Create a start button. */
			start_btn = gtk_button_new_with_label ("Start");
			gtk_box_pack_start (GTK_BOX (hbtn_box), start_btn, TRUE, FALSE, 0);
			g_signal_connect (G_OBJECT (start_btn), "clicked",
							G_CALLBACK (onStartClicked),
							buffer);

			/* Create a stop button. */
			stop_btn = gtk_button_new_with_label ("Stop");
			gtk_box_pack_start (GTK_BOX (hbtn_box), stop_btn, TRUE, FALSE, 0);
			g_signal_connect (G_OBJECT (stop_btn), "clicked",
							G_CALLBACK (onStopClicked),
							buffer);

			gtk_widget_show_all (window);

			gtk_main ();
		}
	}
}


