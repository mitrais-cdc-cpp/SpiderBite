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
		MainUI::MainUI()
		{
		}

		MainUI::~MainUI()
		{
		}

		/* Callback for start button */
		static void onStartClicked (GtkWidget *button, GtkTextBuffer *buffer)
		{
			GtkTextIter start;
			GtkTextIter end;

			gchar *text;

			/* Obtain iters for the start and end of points of the buffer */
			gtk_text_buffer_get_start_iter (buffer, &start);
			gtk_text_buffer_get_end_iter (buffer, &end);

			/* Get the entire buffer text. */
			text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

			/* Print the text */
			g_print ("%s\n", text);

			g_free (text);
		}

		/*Callback for stop button*/
		static void onStopClicked (GtkWidget *button, GtkTextBuffer *buffer)
		{
		}

		/* Callback for open menu */
		static void onOpenClicked(GtkWidget *widget)
		{
			g_print("File -> Open activated.\n");
		}

		/* Callback for quit menu */
		static void onQuitClicked (GtkWidget *widget, gpointer data)
		{
			gtk_main_quit ();
		}


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
			g_signal_connect(G_OBJECT(open), "activate", G_CALLBACK(onOpenClicked), NULL);
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
			gtk_text_buffer_set_text (buffer, "Hello Text View!", -1);

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


