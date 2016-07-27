#include "../inc/WebCrawler.h"
#include "../inc/TextLexer.h"

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

void Mitrais::util::WebCrawler::getContent(const util::UrlTarget& strURL_,
		std::string& result_, bool isHTTPS_)
{
	std::string url = addPrefixAndSufixUrl(strURL_);

	CURL* curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());//url);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result_);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
    curl_easy_setopt(curl, CURLOPT_CAINFO, "./env/ca/ca.crt");
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);//tell curl to output its progress

	curl_easy_perform(curl);

	if(res != CURLE_OK)
	{
		string msg = "cURL_easy_perform() failed: " + string(curl_easy_strerror(res));
		LOG_ERROR << msg;
	}
	else
		LOG_DEBUG << result_;

	// fill buffer
	//buf.insertContentToBuffer(data);

	curl_easy_cleanup(curl);
	curl_global_cleanup();

}
	/**
	 * Gives content of given URL
	 * @param strURL_ valid URL address
	 * @param result_ founded result, commonly HTML source code
	 */
void Mitrais::util::WebCrawler::getContent(const util::UrlTarget& strURL_, std::string& result_)
{
	std::string url = addPrefixAndSufixUrl(strURL_);

	CURL* curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());//url);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, result_);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);//tell curl to output its progress

	res = curl_easy_perform(curl);

	if(res != CURLE_OK)
	{
		string msg = "cURL_easy_perform() failed: " + string(curl_easy_strerror(res));
		LOG_ERROR << msg;
	}
	else
		LOG_DEBUG << result_;

	// fill buffer
	//buf.insertContentToBuffer(data);

	curl_easy_cleanup(curl);
	curl_global_cleanup();
}

/*
 * add prefix (http://www.) and also sufix ("//")
 * @param url (string)
 * @return result with prefix and sufix
 */
string Mitrais::util::WebCrawler::addPrefixAndSufixUrl(const util::UrlTarget& url)
{
	std::string result;

	if (url.Protocol.compare("http") == 0)
	{
		// special case for mitrais.com url
		if (url.Url.length() >= 11)
		{
			if (url.Url.substr(0, 11).compare("mitrais.com") == 0)
			{
				result = "http://www.";
			}
		}
		else
		{
			result = "http://";
		}
	}
	else if (url.Protocol.compare("https") == 0)
	{
		result = "https://";
	}
	else if (url.Protocol.compare("ftp") == 0)
	{
		result = "ftp://";
	}

	result += url.Url;

	std::size_t foundSubPage = url.Url.find("\/");

	if (foundSubPage == std::string::npos)
	{
		result += "/";
	}
	else
	{
		std::string subPageUrl = url.Url.substr(foundSubPage, url.Url.length());

		if (!subPageUrl.empty())
		{
			std::size_t foundSubPageExtension = subPageUrl.find(".");

			if (foundSubPageExtension == std::string::npos)
			{
				result += "/";
			}
		}
	}

	return result;
}
