/*
 * MainModel.hpp
 *
 *  Created on: Jul 28, 2016
 *      Author: developer
 */

#ifndef INC_MODEL_MAINMODEL_HPP_
#define INC_MODEL_MAINMODEL_HPP_

#include <functional>
#include <iostream>
#include "../util/UrlTarget.h"
#include "../util/TextReader.h"
#include "../util/TextWriter.h"
#include "../util/TextBuffer.h"
#include "../util/TextLexer.h"
#include "../util/WebCrawler.h"

namespace Mitrais
{
	namespace Model
	{
		typedef std::function<void()> CallbackFunction;

		class MainModel
		{
		public:
			~MainModel();
			MainModel(MainModel const&) = delete;
			void operator=(MainModel const&) = delete;

			static MainModel* getInstance();

			void run();
			std::vector<Mitrais::util::UrlTarget> readUrlFromFile(std::string filename);
			void writeUrlToFile(std::string filename, bool isSaveAsHtml);
			void writeUrlToDatabase(std::string filename);
			std::vector<std::string> findUrls(std::string content);
			void clearBuffer(vector<std::string> stringBuffer);
			void insertContentToBuffer(vector<std::string> stringBuffer ,string content);
			void crawlContent(const std::string& url, std::string& result);

			void whenApplicationStarts(CallbackFunction callback);
			void whenApplicationStop(CallbackFunction callback);
			void whenCrawlingStart(CallbackFunction callback);
			void whenCrawlingStop(CallbackFunction callback);
			void whenCrawlingRunning(CallbackFunction callback);

		private:
			MainModel();
			CallbackFunction onApplicationStarts;
			CallbackFunction onApplicationStop;
			CallbackFunction onCrawlingStart;
			CallbackFunction onCrawlingStop;
			CallbackFunction onCrawlingRunning;
			static MainModel* m_instance;
		};
	}
}



#endif /* INC_MODEL_MAINMODEL_HPP_ */
