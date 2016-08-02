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
