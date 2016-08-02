#include "../../inc/util/WebCrawler.h"
#include "../../inc/util/TextLexer.h"

/**
 * Ctor
 */
Mitrais::util::WebCrawler::WebCrawler()
{
}

/**
 * Dtor
 */
Mitrais::util::WebCrawler::~WebCrawler()
{

}

/**
 * Callback method, used in CURL to return content
 * @param ptr buffered results, size of buffer is size*nmemb
 * @param size size
 * @param nmemb size
 * @param stream founded content
 * @return
 */
static size_t writeCallback(void *contents, size_t size, size_t nmemb, void* stream)
{
	((std::string*)stream)->append((char*)contents, size * nmemb);

//	string temp(static_cast<const char*>(ptr), size * nmemb);
//	stream = temp;

	return size * nmemb;
}

bool Mitrais::util::WebCrawler::getContent(UrlTarget &url_, bool isHTTPS_)
{
	bool HRESULT = true;
	url_.Content = getContent(url_.Url, isHTTPS_, HRESULT);
	return HRESULT;
}

std::string Mitrais::util::WebCrawler::getContent(const std::string& strURL_, bool isHTTPS_, bool& _isError)
{
	std::string url = addPrefixAndSufixUrl(strURL_);
	std::string result;

	CURL* curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());//url);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);

	if(isHTTPS_)
	{
	    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
	    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
	    curl_easy_setopt(curl, CURLOPT_CAINFO, "./env/ca/ca.crt");
	}

	curl_easy_perform(curl);

	if(res != CURLE_OK)
	{
		LOG_ERROR << "cURL_easy_perform() failed: " << string(curl_easy_strerror(res));
		_isError = true;
	}
	else
		_isError = false;

	curl_easy_cleanup(curl);
	curl_global_cleanup();

	return result;
}

/*
 * add prefix (http://www.) and also sufix ("//")
 * @param url (string)
 * @return result with prefix and sufix
 */
string Mitrais::util::WebCrawler::addPrefixAndSufixUrl(const std::string& url)
{
	std::string result;

	result = "http://www." + url + "/";

	return result;
}

string Mitrais::util::WebCrawler::saveSourceCode(util::UrlTarget &target, util::TextBuffer &buff_)
{
//	string fileName = target.Protocol + "." + target.Url;
//	target.Protocol.
	string fileName = target.Url;

	string strResponse;

	util::TextWriter writer(fileName, buff_.getFullContent());
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
		strResponse = "The "+ fileName + " done!\n"+ "The "+ fileName + " saved";
		if(util::Configuration::getSetting().saveTarget == SAVE_TO_FILE)
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

//vector<Mitrais::util::UrlTarget> Mitrais::util::WebCrawler::getSubUrlList(string content)
//{
//	TextLexer lexer;
//
//	// find the urls
//	std::vector<std::string> vec = lexer.findUrls(content);
//
//	vector<UrlTarget> sublist;
//	for(auto const& str: vec)
//	{
//		UrlTarget target = Mitrais::util::TextReader::getUrl(str);
//		bool isExist = Mitrais::util::TextReader::isUrlExist(target);
//
//		if (!isExist)
//		{
//			sublist.push_back(target);
//		}
//	}
//
//	return sublist;
//}


void Mitrais::util::WebCrawler::crawlSubUrls(WebCrawler &crawler_, util::TextBuffer &buff_, vector<UrlTarget> &vecURL_, int iDeep_)
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
		// check if the url target status is DONE
		if (target.Status == Mitrais::util::UrlTargetStatus::DONE)
		{
			string message = target.Url + " has been crawled previously\n";

			// continue to the next URL target
			continue;
		}

		std::vector<std::string> vec;

		// clear data
		buff_.clearBuffer();
		string data = "";

		// set the status into START
		target.Status = Mitrais::util::UrlTargetStatus::START;

		// crawl the web and save into buffer
		crawler_.getContent(target, false);

		// update the status into CRAWLING
		target.Status = Mitrais::util::UrlTargetStatus::CRAWLING;

		//insert into buffer
		buff_.insertContentToBuffer(target.Content);

		// save into file
		saveSourceCode(target, buff_);

		// update the status into DONE
		target.Status = Mitrais::util::UrlTargetStatus::DONE;

//		target.SubUrlList = getSubUrlList(data);
		util::TextLexer lexer;
		target.SubUrlList = lexer.findUrls(target);
		target.Deepness = iDeep_;

		// Crawl the sub urls
		crawlSubUrls(crawler_, buff_, target.SubUrlList, iDeep_);
	}
}

int Mitrais::util::WebCrawler::crawlWebsite(UrlTarget &args)
{
	 util::UrlTarget *target;
	 target = &args;

	 std::string msg = "";
	 msg = target->Url + " started crawling...!";
	 LOG_INFO << msg;

	 WebCrawler crawler;
	 util::TextBuffer buff;
	 util::TextLexer lexer;

	 // check if the url target status is DONE
	 if (target->Status == Mitrais::util::UrlTargetStatus::DONE)
	 {
		  // show message
		  string message = target->Url + " has been crawled previously.\n";
	 }
	 else
	 {
		  // URL was not crawled. Crawl it now
		  msg = target->Url + " started crawling...!";
		  LOG_INFO << msg;

		  // clear data
		  buff.clearBuffer();
		  string data = "";

		  // update the status into START
		  target->Status = Mitrais::util::UrlTargetStatus::START;

		  // crawl the web and save into buffer
		  crawler.getContent(*target, false);

		  // update the status into CRAWLING
		  target->Status = Mitrais::util::UrlTargetStatus::CRAWLING;

		  //insert into buffer
		  buff.insertContentToBuffer(target->Content);

		  // update the status into DONE
		  target->Status = Mitrais::util::UrlTargetStatus::DONE;

		  // save into the targeted media
		  saveSourceCode(*target, buff);

		  target->SubUrlList = lexer.findUrls(*target);

		  // crawl the sub urls
		  crawlSubUrls(crawler, buff, target->SubUrlList, 0);
	}

	return 0;
}
