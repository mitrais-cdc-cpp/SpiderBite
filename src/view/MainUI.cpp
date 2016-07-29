/*
 * MainUI.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: adityo_w
 */

#include "../../inc/view/MainUI.h"

#include "../../inc/view/SettingView.hpp"

namespace Mitrais
{
	namespace UI
	{
		GtkWidget *_start_btn;
		GtkWidget *_stop_btn;
		GtkTextBuffer *_buffer;
		GtkWidget *text_view;
		GtkWidget *save;
		GtkWidget *status_bar;// = gtk_statusbar_new();
		gint context_id;// = gtk_statusbar_get_context_id(GTK_STATUSBAR (status_bar), "Status bar");

		std::string _filePath;
		vector<util::UrlTarget> _targets;

		/**
		 * Default constructor of MainUI
		 */
		MainUI::MainUI()
		{
		}

		/**
		 * Destroyer of MainUIl
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

		/**
		 * Push text message to status bar.
		 * @Params message a message to display
		 */
		void pushMessage(std::string message)
		{
			gtk_statusbar_push (GTK_STATUSBAR (status_bar), GPOINTER_TO_INT (context_id), convertStringToPChar(message));
		}

		/*
		 * Set enable or disable button based on file path (empty or not)
		 */
		static void setButtonAndMenuDisability()
		{
			if (_filePath.empty())
			{
				// disable start and stop button
				gtk_widget_set_sensitive (_start_btn, FALSE);
				gtk_widget_set_sensitive (_stop_btn, FALSE);

				// disable save menu
				gtk_widget_set_sensitive(save, FALSE);
			}
			else
			{
				// enable start and stop button
				gtk_widget_set_sensitive (_start_btn, TRUE);
				gtk_widget_set_sensitive (_stop_btn, FALSE);

				// enable save menu
				gtk_widget_set_sensitive(save, TRUE);
			}
		}


		/**
		* Display file content to UI
		*/
		void displayFileContent()
		{

		}

		/**
		 * saveSourceCode function to save the buffer into file
		 * @param strURL_ the target url
		 * @param buff_ the TextBuffer
		 * @return save status in string
		 */
		static string saveSourceCode(string strURL_, util::TextBuffer buff_)
		{
			string strResponse;

			util::TextWriter writer(strURL_, buff_.getFullContent());
			util::BaseResponse responseWrite;

			if(util::Configuration::getSetting().saveTarget == SAVE_TO_FILE)
			{
				// save into file
				writer.writeToFile(responseWrite, true);
			}
			else
			{
				// save to database
				writer.writeToDatabase(responseWrite);
			}

			// check the response status
			if (responseWrite.getStatus())
			{
				strResponse = "The "+ strURL_ + " done!\n"+ "The "+ strURL_+ " saved";
				if(util::Configuration::getSetting().saveTarget == SAVE_TO_FILE)
				{
					strResponse += ": "+ strURL_ +".html on current application folder\n";
				}
				else
				{
					strResponse += " on database\n";
				}

				LOG_INFO << strURL_ + " Saved!";
			}
			else
			{
				strResponse = "Can't connect to: "+ strURL_ + "n"+
					   "Skip " + strURL_ +" target\n"+
						"----------------------------------------------------------------------------\n";
				LOG_ERROR << "Can't connect to: "+ strURL_;
			}

			return strResponse;
		}

		/**
		 * getSubUrlList function to get list of UrlTarget
		 * @param content: the string content
		 * @return the vector of UrlTarget
		 */
		static vector<UrlTarget> getSubUrlList(string content)
		{
			TextLexer lexer;

			// find the urls
			std::vector<std::string> vec = lexer.findUrls(content);

			//
			vector<UrlTarget> sublist;
			for(auto const& str: vec)
			{
				UrlTarget target;
				target.Url = str;
				sublist.push_back(target);
			}

			return sublist;
		}

		/**
		 * crawlSubUrls function to crawl the web from given urls target
		 * @param crawler_ : the web crawler reference
		 * @param buff_ : the text buffer reference
		 * @param vecURL_ : the url target reference
		 * @param iDeep_ : the deep of crawled content
		 */
		void crawlSubUrls(WebCrawler &crawler_, util::TextBuffer &buff_, vector<UrlTarget> &vecURL_, int iDeep_ = 2)
		{
	        Mitrais::util::TextLexer lexer;
	        vector<UrlTarget> vecTemp = vecURL_;

			util::Configuration config;
	        if(iDeep_ == config.getSetting().crawlingDeepness)
	        	return;
	        else
	        	++iDeep_;

			for(auto &target: vecURL_)
			{
				std::vector<std::string> vec;

				// clear data
				buff_.clearBuffer();
				string data = "";

				// crawl the web and save into buffer
				crawler_.getContent(target, true);

				//insert into buffer
				buff_.insertContentToBuffer(data);

				// save into file
				saveSourceCode(target.Url, buff_);

				target.SubUrlList = getSubUrlList(data);
				target.Deepness = iDeep_;

				// Crawl the sub urls
				crawlSubUrls(crawler_, buff_, target.SubUrlList, iDeep_);
			}
		}


		/**
		 * Callback method for start button
		 * @params button a GtkWidget pointer
		 * @params buffer a GtkTextBuffer pointer
		 */
		static void onStartClicked (GtkWidget *button, GtkTextBuffer *buffer)
		{
			LOG_INFO << "Crawling web started";
			string saveStatus;
			gchar* text;
			GtkTextIter ei;
			std::string msg = "";

			int deepness = 2;

			//set textview readonly
			/**
			 * TODO:
			 * replce these 4 lines of code below by calling
			 * disableControlsWhenStartClicked()
			 */
			gtk_text_view_set_editable (GTK_TEXT_VIEW (text_view), FALSE);
			gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (text_view), FALSE);
			gtk_text_buffer_set_text (buffer, "", -1);
			gtk_widget_set_sensitive (button, FALSE);

			if (_targets.size() > 0)
			{
				util::TextBuffer buff;
				WebCrawler crawler;

				for(auto& target: _targets)
				{
					msg = target.Url + " started crawling...!";
					LOG_INFO << msg;

					// clear data
					buff.clearBuffer();
					string data = "";

					// crawl the web and save into buffer
					crawler.getContent(target, true);
					//insert into buffer
					buff.insertContentToBuffer(data);

					// save into file
					saveStatus = saveSourceCode(target.Url, buff);

			        target.SubUrlList = getSubUrlList(data);;

			        // crawl the sub urls
				    crawlSubUrls(crawler, buff, target.SubUrlList, 0);

				    /**
				     * TODO:
				     * replace 3 lines of code below in MVP project
				     * with appendStringToTextBox() method
				     */
					text = convertStringToPChar(saveStatus);
					gtk_text_buffer_get_end_iter(buffer, &ei);
					gtk_text_buffer_insert(buffer, &ei, text, -1);
				}
			}
			else
			{
				pushMessage("File loaded but no URL targets found.");

				msg = "File loaded but no URL targets to crawl.";
				LOG_WARN << msg;
			}

			// enable stop button
			gtk_widget_set_sensitive (_stop_btn, TRUE);
			pushMessage("Crawling stopped.");
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

		}

		/**
		 * Callback method for quit menu
		 * params widget a GtkWidget pointer
		 */
		static void onQuitClicked (GtkWidget *widget, gpointer data)
		{
		}

		/**
		 * To save file
		 * @params char *filename a char of filename
		 */
		void saveToFile(char *filename)
		{
			pushMessage("Saving..");

			GtkTextIter start;
			GtkTextIter end;
			gchar *text;
			GtkTextIter ei;

			gtk_text_buffer_get_start_iter(_buffer, &start);
			gtk_text_buffer_get_end_iter(_buffer, &end);
			text = gtk_text_buffer_get_text(_buffer, &start, &end, FALSE);

			string textString = string(text);
			string filenameString = string(filename);

			Mitrais::util::TextWriter writer(filenameString, textString);
			Mitrais::util::BaseResponse response;
			writer.writeToFile(response, false);

			LOG_INFO << "Save file: " + filenameString;
		}

		/**
		 * Callback method for save menu
		 * @params GtkWidget *widget a widget
		 * @params GtkWidget *window a window
		 */
		static void onSaveClicked(GtkWidget *widget, GtkWidget *window)
		{

		}

		/**
		 * Callback method for setting menu
		 * @param argc an integer
		 * @param argv an array of chars pointer
		 */
		static void onSettingClicked(int argc, char *argv[])
		{

			//TODO: refactor MVP
			//PropertyUI prop;
			//prop.activateUI(argc, argv);
		}

		/**
		 * check the parameter
		 * @param int argc (number of parameter that to be passed)
		 * @param char* argv (the parameter value that be passed)
		 */
		void checkParameter(int argc, char* argv[])
		{
			// check the number of argument, if the argument is more than 1
			if (argc > 1)
			{
				// set the second argument as file path
				_filePath = string(argv[1]);

				// press start button
				onStartClicked(_start_btn, _buffer);
			}
		}



		/**
		 * Activates the UI
		 * params argc an integer
		 * params argv an array of chars pointer
		 */
		void MainUI::activateUI(int argc, char *argv[])
		{
		}


	}
}
