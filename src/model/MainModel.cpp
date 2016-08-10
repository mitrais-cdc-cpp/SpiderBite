/*
 * MainModel.cpp
 *
 *  Created on: Jul 28, 2016
 *      Author: developer
 */

#include "../../inc/model/MainModel.hpp"

using namespace Mitrais::Model;

// give value or just instantiate static members
MainModel* MainModel::m_instance = nullptr;
std::vector<Mitrais::util::UrlTarget> MainModel::urls;

// Main model ctor
MainModel::MainModel()
: _bInitialReadingDone(false)
{}

// Main model desc
MainModel::~MainModel()
{
//	if(m_instance)
//		delete m_instance;
}

// singleton of m_instance
MainModel* MainModel::getInstance()
{
	if(!m_instance)
		m_instance = new MainModel();
	return m_instance;
}

/**
 * When app starts callback
 * @param callback
 */
void MainModel::whenApplicationStarts(CallbackFunction callback)
{
	onApplicationStarts = callback;
}

/**
 * When app stop callback
 * @param callback
 */
void MainModel::whenApplicationStop(CallbackFunction callback)
{
	onApplicationStop = callback;
}

/**
 * when crawling start callback
 * @param callback
 */
void MainModel::whenCrawlingStart(CallbackFunction callback)
{
	onCrawlingStart = callback;
}

/**
 * when crawling stop callback
 * @param callback
 */
void MainModel::whenCrawlingStop(CallbackFunction callback)
{
	onCrawlingStop = callback;
}

/**
 * when crawling running callback
 * @param callback
 */
void MainModel::whenCrawlingRunning(CallbackFunction callback)
{
	onCrawlingRunning = callback;
}

/**
 * run method to call on app start
 */
void MainModel::run()
{
	onApplicationStarts();
}

/**
 * stop method to call app stop
 */
void MainModel::stop()
{
	onApplicationStop();
}

/**
 * read url from file name
 * @param filename
 * @return
 */
bool MainModel::readUrls(std::string filename)
{
	_strUrlFilename = filename;
	return readUrlFromFile();
}

/**
 * read url from file and gets the url
 * @return
 */
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

/**
 * write the url to database or file
 * @param enum_
 */
Mitrais::util::BaseResponse MainModel::writeUrls(std::string filepath, std::string content, const util::UrlTarget& target)
{
	util::TextWriter writer(filepath, content, target);
	util::BaseResponse responseWrite;

	util::SaveModeEnum enum_ = util::Configuration::getSetting().saveTarget;
	switch(enum_)
	{
		case Mitrais::util::SaveModeEnum::SAVE_TO_FILE:
		{
			// save into file
			writer.writeToFile(responseWrite, true);
			break;
		}
		case Mitrais::util::SaveModeEnum::SAVE_TO_DB:
		{
			// save to database
			writer.writeToDatabase(responseWrite);
			break;
		}
		default:
		{
			LOG_WARN << "not save method set!";
		}
	}

	return responseWrite;
}

/**
 * stop crawling method
 * @return
 */
bool MainModel::stopCrawling()
{
	//todo
}

/**
 * Method to check configuration file setting.
 * If the configuration file is not exist this method will create \n
 * the default configuration file.
 */
void MainModel::checkConfigSetting()
{
	if(!boost::filesystem::exists(_configFileName.c_str()))
	{

		Mitrais::util::ConfigSettings settings("localhost",
						27017,
						"SpiderBite",
						"SpiderBite",
						1,
						util::SAVE_TO_FILE,
						"./");

		_xmlHelper.saveXML(settings, _configFileName.c_str());

		LOG_INFO << "Default configuration file saved!";
	}
}

Mitrais::util::ConfigSettings* MainModel::loadXMLConfiguration()
{
	if(boost::filesystem::exists(_configFileName.c_str()))
	{
		LOG_INFO << "Config loaded";
		_xmlHelper.loadXML(_settings, _configFileName.c_str());
		return &(_settings);
	} else {
		LOG_INFO << "Config not found";
		return nullptr;
	}
}

/**
 * Start crawling function
 *
 * @param urls
 * @return
 */
bool MainModel::startCrawling(std::vector<Mitrais::util::UrlTarget> urls)
{
	LOG_INFO << "start crawling thread";

	std::string result;
	bool isError = false;
	int targetCount = urls.size();

	if (targetCount > 0)
	{
		_helper.executeAsyncBoost(crawlWebsite, urls);
	}
	else
	{
		LOG_WARN << "File loaded but no URL targets to crawl.";
	}

	LOG_INFO << "stop crawling thread";

	return isError;
}

/**
 * Convert from enum to string
 *
 * @param v
 * @return
 */
const char* MainModel::toString(util::UrlTargetProtocol v)
{
	switch (v)
	{
		case util::UrlTargetProtocol::NONE:   return "none";
		case util::UrlTargetProtocol::HTTP:   return "http";
		case util::UrlTargetProtocol::HTTPS: return "https";
		case util::UrlTargetProtocol::FTP: return "ftp";
		case util::UrlTargetProtocol::IMAGE: return "image";
		default:      return "uknown";
	}
}

/**
 * Save source code after crawling process
 *
 * @param target
 * @param buff_
 * @return
 */
string MainModel::saveSourceCode(util::UrlTarget &target, util::TextBuffer &buff_)
{
	LOG_INFO << "start save source code";
	string protocol = toString(target.Protocol);
	string fileName = protocol + "." + target.Url;

	string strResponse;

	// write urls
	util::BaseResponse responseWrite = writeUrls(fileName, buff_.getFullContent(), target);

	// check the response status
	if (responseWrite.getStatus())
	{
		strResponse = "The "+ fileName + " done!\n"+ "The "+ fileName + " saved";
		if(util::Configuration::getSetting().saveTarget == util::SAVE_TO_FILE)
		{
			string savePath = util::Configuration::getSetting().pathToLocalDir;
			if (!savePath.empty())
			{
				strResponse += ": "+ savePath +"\/" + fileName +".html\n";
			}
			else
			{
				strResponse += ": "+ fileName +".html on current application folder\n";
			}
		}
		else
		{
			strResponse += " on database\n";
		}

		LOG_INFO << fileName + " Saved!";
	}
	else
	{
		strResponse = "Can't connect to: "+ fileName + "n"+
			   "Skip " + fileName +" target\n"+
				"----------------------------------------------------------------------------\n";

		LOG_ERROR << "Can't connect to: "+ fileName;
	}

	return strResponse;
}

void MainModel::proceedCrawl(util::TextBuffer &buff_, util::UrlTarget &target,
		util::WebCrawler &crawler_, util::TextLexer lexer, vector<util::UrlTarget> &vecURL_,
		int iDeep_)
{
	// clear data
	buff_.clearBuffer();
	target.Content = "";

	// crawl the web and save into buffer
	crawler_.getContent(target, false);

	//insert into buffer
	buff_.insertContentToBuffer(target.Content);

	// save into file
	saveSourceCode(target, buff_);

	target.SubUrlList = lexer.findUrls(target.Content, vecURL_);
	target.Deepness = iDeep_;

	// Crawl the sub urls
	crawlSubUrls(crawler_, buff_, target.SubUrlList, iDeep_);
}

/**
 * Crawl sub Url
 *
 * @param crawler_
 * @param buff_
 * @param vecURL_
 * @param iDeep_
 */
void MainModel::crawlSubUrls(util::WebCrawler &crawler_, util::TextBuffer &buff_, vector<util::UrlTarget> &vecURL_, int iDeep_)
{
	Mitrais::util::TextLexer lexer;
	vector<util::UrlTarget> vecTemp = vecURL_;

	util::Configuration config;
	if(iDeep_ == config.getSetting().crawlingDeepness)
		return;
	else
		++iDeep_;

	for(auto &target: vecURL_)
	{
		// check if the url target status is DONE
		if (target.Status == Mitrais::util::UrlTargetStatus::DONE)
		{
			string message = target.Url + " has been crawled previously\n";

			// continue to the next URL target
			continue;
		}

		// proceed crawl
		proceedCrawl(buff_, target, crawler_, lexer, vecURL_, iDeep_);
	}
}

/**
 * crawl the website
 *
 * @param target
 * @return int
 */

int MainModel::crawlWebsite(util::UrlTarget &target)
{
	 std::string msg = "";
	 msg = target.Url + " started crawling...!";
	 LOG_INFO << msg;

	 util::WebCrawler crawler;
	 util::TextBuffer buff;
	 util::TextLexer lexer;

	 // check if the url target status is DONE
	 if (target.Status == Mitrais::util::UrlTargetStatus::DONE)
	 {
		  // show message
		  string message = target.Url + " has been crawled previously.\n";
	 }
	 else
	 {
		  // URL was not crawled. Crawl it now
		  msg = target.Url + " started crawling...!";
		  LOG_INFO << msg;

		  // proceed crawl
		  proceedCrawl(buff, target, crawler, lexer, urls, 0);
	}

	msg = target.Url + " crawling stopped!";
	LOG_INFO << msg;

	return 0;
}

/*
 * Save the URLs into file
 *
 * @param filename
 * @param content
 */
void MainModel::saveUrls(std::string fileName, std::string content)
{
	util::TextWriter writer(fileName, content);
	util::BaseResponse response;
	writer.writeToFile(response, false);
}
