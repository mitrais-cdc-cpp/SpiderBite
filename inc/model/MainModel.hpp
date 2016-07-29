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
#include "../util/SaveModeEnum.h"

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

			//events;
			void run();
			void stop();

			//public interface;
			bool startCrawling(std::vector<Mitrais::util::UrlTarget> urls);
			bool stopCrawling();
			bool readUrls(std::string filename);
			bool writeUrls(Mitrais::util::SaveModeEnum enum_);

			//registered events
			void whenApplicationStarts(CallbackFunction callback);
			void whenApplicationStop(CallbackFunction callback);
			void whenCrawlingStart(CallbackFunction callback);
			void whenCrawlingStop(CallbackFunction callback);
			void whenCrawlingRunning(CallbackFunction callback);

			//Getter
			inline std::string getUrlFilename() { return _strUrlFilename; }
			inline bool getInitialReading() { return _bInitialReadingDone; }
			inline std::vector<Mitrais::util::UrlTarget> getUrls() { return urls; }

		private:
			MainModel();
			CallbackFunction onApplicationStarts;
			CallbackFunction onApplicationStop;
			CallbackFunction onCrawlingStart;
			CallbackFunction onCrawlingStop;
			CallbackFunction onCrawlingRunning;
			static MainModel* m_instance;

			//setter
			inline void setInitialReading(bool value) { _bInitialReadingDone = value; }
			inline void setUrls(std::vector<Mitrais::util::UrlTarget> value) { urls = value; }

			//helper
			std::vector<Mitrais::util::UrlTarget> findUrls(Mitrais::util::UrlTarget url);
			bool readUrlFromFile(std::string filename);
			bool readUrlFromDatabase();
			void writeUrlToFile(std::string filename, bool isSaveAsHtml);
			void writeUrlToDatabase(std::string filename);

			//member
			std::string _strUrlFilename;
			bool _bInitialReadingDone;
			std::vector<Mitrais::util::UrlTarget> urls;
		};
	}
}



#endif /* INC_MODEL_MAINMODEL_HPP_ */
