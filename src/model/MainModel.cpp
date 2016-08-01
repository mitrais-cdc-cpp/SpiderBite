/*
 * MainModel.cpp
 *
 *  Created on: Jul 28, 2016
 *      Author: developer
 */

#include "../../inc/model/MainModel.hpp"

using namespace Mitrais::Model;

MainModel* MainModel::m_instance = nullptr;

MainModel::MainModel()
: _bInitialReadingDone(false)
{}

MainModel::~MainModel()
{
	delete m_instance;
}

MainModel* MainModel::getInstance()
{
	if(!m_instance)
		m_instance = new MainModel();
	return m_instance;
}

void MainModel::whenApplicationStarts(CallbackFunction callback)
{
	onApplicationStarts = callback;
}

void MainModel::whenApplicationStop(CallbackFunction callback)
{
	onApplicationStop = callback;
}

void MainModel::whenCrawlingStart(CallbackFunction callback)
{
	onCrawlingStart = callback;
}

void MainModel::whenCrawlingStop(CallbackFunction callback)
{
	onCrawlingStop = callback;
}

void MainModel::whenCrawlingRunning(CallbackFunction callback)
{
	onCrawlingRunning = callback;
}

void MainModel::run()
{
	onApplicationStarts();
}

void MainModel::stop()
{
	onApplicationStop();
}

bool MainModel::readUrls(std::string filename)
{
	_strUrlFilename = filename;
	return readUrlFromFile();
}



bool MainModel::readUrlFromFile()
{
	try
	{
		if(!_bInitialReadingDone)
		{
			util::TextReader 	reader(_strUrlFilename);
			util::BaseResponse 	response;
			setInitialReading(true);
			urls = reader.getUrls(response);
		}
	}
	catch(std::exception& ex)
	{
		LOG_ERROR << "An error occured: " << ex.what();
		return false;
	}

	return true;
}

void MainModel::writeUrls(Mitrais::util::SaveModeEnum enum_)
{
	switch(enum_)
	{
		case Mitrais::util::SaveModeEnum::SAVE_TO_FILE:
		{
			writeUrlToFile("bla", true);
			break;
		}
		case Mitrais::util::SaveModeEnum::SAVE_TO_DB:
		{
			writeUrlToDatabase("bla");
			break;
		}
		default:
		{
			LOG_WARN << "not save method set!";
		}
	}
}
void MainModel::writeUrlToFile(std::string filename, bool isSaveAsHtml)
{
	util::TextWriter writer(filename);
	util::BaseResponse response;
	writer.writeToFile(response, isSaveAsHtml);
}

void MainModel::writeUrlToDatabase(std::string filename)
{
	util::TextWriter writer(filename);
	util::BaseResponse response;
	writer.writeToDatabase(response);
}

std::vector<Mitrais::util::UrlTarget> MainModel::findUrls(Mitrais::util::UrlTarget url)
{
	util::TextLexer lexer;
	return lexer.findUrls(url);
}

bool MainModel::stopCrawling()
{
	//todo
}

bool MainModel::startCrawling(std::vector<Mitrais::util::UrlTarget> urls, int iDeep_)
{
	util::WebCrawler crawler;
	std::string result;
	bool isError = false;

	if(iDeep_ == _config.getSetting().crawlingDeepness)
			return true;
		else
			++iDeep_;

	for(auto& url : urls)
	{
		url.Status = Mitrais::util::UrlTargetStatus::START;

		crawler.getContent(url, isError);

		if (isError)
			url.Status = Mitrais::util::UrlTargetStatus::DONE;
		else
			url.Status = Mitrais::util::UrlTargetStatus::ERROR;

		//seach deeper URLS
		url.SubUrlList = findUrls(url);

		startCrawling(url.SubUrlList, iDeep_);
	}



	return isError;

}

//void MainModel::crawlSubUrls(vector<Mitrais::util::UrlTarget> &vecURL_, int iDeep_ = 2)
//{
//	Mitrais::util::TextLexer lexer;
//
//	Mitrais::util::Configuration config;
//	if(iDeep_ == config.getSetting().crawlingDeepness)
//		return;
//	else
//		++iDeep_;
//
//	for(auto &target: vecURL_)
//	{
//		// check if the url target status is DONE
//		if (target.Status == UrlTargetStatus::DONE)
//		{
//			// continue to the next URL target
//			continue;
//		}
//
//		std::vector<std::string> vec;
//
//		// clear data
//		buff_.clearBuffer();
//		string data = "";
//
//		// set the status into START
//		target.Status = UrlTargetStatus::START;
//
//		// crawl the web and save into buffer
//		crawler_.getContent(target, false);
//
//		// update the status into CRAWLING
//		target.Status = UrlTargetStatus::CRAWLING;
//
//		//insert into buffer
//		buff_.insertContentToBuffer(data);
//
//		// save into file
//		saveSourceCode(target, buff_);
//
//		// update the status into DONE
//		target.Status = UrlTargetStatus::DONE;
//
//		target.SubUrlList = getSubUrlList(data);
//		target.Deepness = iDeep_;
//
//		// Crawl the sub urls
//		crawlSubUrls(crawler_, buff_, target.SubUrlList, iDeep_);
//	}
//}
