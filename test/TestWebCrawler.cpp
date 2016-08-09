#include "TestWebCrawler.h"

/*
 * test whether the status is NONE or not
 */
void TestWebCrawler::testWebCrawlerStatusNone()
{
	Mitrais::util::UrlTarget target;
	target.Url = "mitrais.com";
	target.Protocol = Mitrais::util::UrlTargetProtocol::HTTP;
	target.Status = Mitrais::util::UrlTargetStatus::NONE;
	target.Deepness = 0;

	Mitrais::util::UrlTargetStatus actualStatus = Mitrais::util::UrlTargetStatus::NONE;

	CPPUNIT_ASSERT(actualStatus == target.Status);
}

/*
 * test whether the status is DONE or not
 */
void TestWebCrawler::testWebCrawlerStatusDone()
{
	Mitrais::util::UrlTarget target;
	target.Url = "mitrais.com";
	target.Status = Mitrais::util::UrlTargetStatus::NONE;
	target.Protocol = Mitrais::util::UrlTargetProtocol::HTTP;
	target.Deepness = 0;

	Mitrais::util::WebCrawler crawler;
	crawler.getContent(target, false);

	Mitrais::util::UrlTargetStatus actualStatus = Mitrais::util::UrlTargetStatus::DONE;

	CPPUNIT_ASSERT(actualStatus == target.Status);
}

/*
 * test whether the status is Error or not
 */
void TestWebCrawler::testWebCrawlerStatusError()
{
	Mitrais::util::UrlTarget target;
	target.Url = "mitrais.com";
	target.Status = Mitrais::util::UrlTargetStatus::NONE;
	target.Protocol = Mitrais::util::UrlTargetProtocol::HTTPS;
	target.Deepness = 0;

	Mitrais::util::WebCrawler crawler;
	crawler.getContent(target, true);

	Mitrais::util::UrlTargetStatus actualStatus = Mitrais::util::UrlTargetStatus::ERROR;

	CPPUNIT_ASSERT(actualStatus == target.Status);
}
