#include "../inc/WebCrawler.h"

Mitrais::util::WebCrawler::WebCrawler()
{

}

Mitrais::util::WebCrawler::~WebCrawler()
{

}

static size_t writeCallback(void *ptr, size_t size, size_t nmemb, std::string stream)
{
    string temp(static_cast<const char*>(ptr), size * nmemb);
    stream = temp;
    return size*nmemb;
}

void Mitrais::util::WebCrawler::getContent(const std::string& strURL_, std::string& result)
{
    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, strURL_.c_str());//strURL_);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, result);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress

    curl_easy_perform(curl);

    LOG_DEBUG << result;

    // fill buffer
	//buf.insertContentToBuffer(data);

    curl_easy_cleanup(curl);
    curl_global_cleanup();
}
