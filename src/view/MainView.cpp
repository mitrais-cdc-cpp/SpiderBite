/*
 * MainView.cpp
 *
 *  Created on: Jul 26, 2016
 *      Author: developer
 */

#include "../../inc/view/MainView.hpp"

using namespace Mitrais::View;

MainView* MainView::m_instance = nullptr;

MainView::MainView()
{}

MainView::~MainView()
{
	delete m_instance;
}

MainView* MainView::getInstance()
{
	if(!m_instance)
		m_instance = new MainView();

	return m_instance;
}

void MainView::onSaveClicked(CallbackFunction callback)
{
	whenSaveClicked = callback;
}

void MainView::onQuitClicked(CallbackFunction callback)
{
	whenQuitClicked = callback;
}

void MainView::onOpenClicked(CallbackFunction callback)
{
	whenOpenClicked = callback;
}

void MainView::onStopClicked(CallbackFunction callback)
{
	whenStopClicked = callback;
}

void MainView::onStartClicked(CallbackFunction callback)
{
	whenStartClicked = callback;
}

void MainView::onSettingViewClicked(CallbackFunction callback)
{
	whenSettingClicked = callback;
}

void MainView::saveClicked(GtkWidget *widget, GtkWidget *window)
{
	MainView::getInstance()->whenSaveClicked();
}

void MainView::quitClicked(GtkWidget *widget, gpointer data)
{
	MainView::getInstance()->whenQuitClicked();
}

void MainView::openClicked(GtkWidget *widget, GtkWidget *window)
{
	MainView::getInstance()->whenOpenClicked();
}

void MainView::stopClicked(GtkWidget *button, GtkTextBuffer *buffer)
{
	MainView::getInstance()->whenStopClicked();
}

void MainView::startClicked(GtkWidget* button, GtkTextBuffer* buffer)
{
	MainView::getInstance()->whenStartClicked();
}

void MainView::settingClicked()
{
	MainView::getInstance()->whenSettingClicked();
}

void MainView::setButtonAndMenuDisability()
{
	if (_filePath.empty())
	{
		// disable start and stop button
		gtk_widget_set_sensitive (_startBtn, FALSE);
		gtk_widget_set_sensitive (_stopBtn, FALSE);

		// disable save menu
		gtk_widget_set_sensitive(_save, FALSE);
	}
	else
	{
		// enable start and stop button
		gtk_widget_set_sensitive (_startBtn, TRUE);
		gtk_widget_set_sensitive (_stopBtn, FALSE);

		// enable save menu
		gtk_widget_set_sensitive(_save, TRUE);
	}
}

GtkTextBuffer* MainView::getPTextBuffer(GtkWidget* widget)
{
	return gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
}

void MainView::setTextBuffer(std::string str)
{
	gtk_text_buffer_set_text (_textBuffer, str.c_str(), -1);
}

void MainView::clearTextBox()
{
	_textBuffer = getPTextBuffer(_txtBox);
	setTextBuffer("");
}

void MainView::setStringToTextBox(std::string str)
{
	_textBuffer = getPTextBuffer(_txtBox);
	setTextBuffer(str);
}

void MainView::appendStringToTextBox(std::string str)
{
	GtkTextIter end;

	gtk_text_buffer_get_end_iter(_textBuffer, &end);
	gtk_text_buffer_insert(_textBuffer, &end, str.c_str(), -1);
}

std::string MainView::getStringFromTextBuffer()
{
	GtkTextIter start,end;

	gtk_text_buffer_get_start_iter(_textBuffer, &start);
	gtk_text_buffer_get_end_iter(_textBuffer, &end);
	return gtk_text_buffer_get_text(_textBuffer, &start, &end, FALSE);
}

void MainView::build()
{
	/* Create a Window. */
	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Spiderbite");

	/* Set a decent default size for the window. */
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
	g_signal_connect (G_OBJECT (window), "destroy",
					G_CALLBACK (quitClicked),
					NULL);

	GtkWidget *vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	/* Create menubar and the menu list itself.*/
	GtkWidget *menubar = gtk_menu_bar_new();
	GtkWidget *filemenu = gtk_menu_new();
	GtkWidget *file = gtk_menu_item_new_with_label("File");
	GtkWidget *open = gtk_menu_item_new_with_label("Open");
	_save = gtk_menu_item_new_with_label("Save");
	GtkWidget *setting = gtk_menu_item_new_with_label("Setting");
	GtkWidget *quit = gtk_menu_item_new_with_label("Quit");

	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), _save);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), setting);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);

	//Connects GCallback function open_activated to "activate" signal for "open" menu item
	g_signal_connect(G_OBJECT(open), "activate",
			G_CALLBACK(openClicked), window);

	//Connects GCallback function quit_activated to "activate" signal for "save" menu item
	g_signal_connect(G_OBJECT(_save), "activate",
			G_CALLBACK(saveClicked), window);

	//Connects GCallback function quit_activated to "activate" signal for "setting" menu item
	g_signal_connect(G_OBJECT(setting), "activate",
			G_CALLBACK(settingClicked), window);

	//Connects GCallback function quit_activated to "activate" signal for "quit" menu item
	g_signal_connect(G_OBJECT(quit), "activate",
			G_CALLBACK(quitClicked), window);

	/* Create a multiline text widget. */
	_txtBox = gtk_text_view_new ();
	gtk_text_view_set_editable (GTK_TEXT_VIEW (_txtBox), FALSE);
	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (_txtBox), FALSE);
	gtk_box_pack_start (GTK_BOX (vbox), _txtBox, TRUE, TRUE, 0);

	clearTextBox();

	/* Create a horizontal button box */
	GtkWidget *hbtn_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_button_box_set_layout (GTK_BUTTON_BOX(hbtn_box), GTK_BUTTONBOX_END);
	gtk_container_add (GTK_CONTAINER (vbox), hbtn_box);

	/* Create a start button. */
	_startBtn = gtk_button_new_with_label ("Start");
	gtk_box_pack_start (GTK_BOX (hbtn_box), _startBtn, TRUE, FALSE, 0);
	g_signal_connect (G_OBJECT (_startBtn), "clicked",
			G_CALLBACK (startClicked),_textBuffer);

	/* Create a stop button. */
	_stopBtn = gtk_button_new_with_label ("Stop");
	gtk_box_pack_start (GTK_BOX (hbtn_box), _stopBtn, TRUE, FALSE, 0);
	g_signal_connect (G_OBJECT (_stopBtn), "clicked",
			G_CALLBACK (stopClicked),_textBuffer);

	// set button and menu disability
	setButtonAndMenuDisability();

	/* Create status bar */
	GtkWidget *status_bar = gtk_statusbar_new();
	gtk_box_pack_start (GTK_BOX (vbox), status_bar, FALSE, FALSE, 0);
	gtk_widget_show (status_bar);

	gint context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR (status_bar), "Status bar");

	gtk_widget_show_all(window);
}

void MainView::start()
{
	gtk_main();
}
