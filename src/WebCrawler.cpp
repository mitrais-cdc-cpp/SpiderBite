#include "../inc/WebCrawler.h"

Mitrais::util::WebCrawler::WebCrawler()
{

}

Mitrais::util::WebCrawler::~WebCrawler()
{

}

std::string data;

static size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{
	//callback must have this declaration
	//buf is a pointer to the data that curl has for us
	//size*nmemb is the size of the buffer

	for (int c = 0; c<size*nmemb; c++)
	{
	   data.push_back(buf[c]);
	}

	return size*nmemb; //tell curl how many bytes we handled
}

Mitrais::util::TextBuffer Mitrais::util::WebCrawler::getContent(std::string strURL_)
{
	Mitrais::util::TextBuffer buf;

    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, strURL_);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress

    curl_easy_perform(curl);

    //cout << endl << data << endl;

    // fill buffer
	buf.insertContentToBuffer(data);

    curl_easy_cleanup(curl);
    curl_global_cleanup();

	return buf;
}
