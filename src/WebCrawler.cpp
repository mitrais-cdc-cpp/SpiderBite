#include "../inc/WebCrawler.h"

Mitrais::util::WebCrawler::WebCrawler()
{

}

Mitrais::util::WebCrawler::~WebCrawler()
{

}

Mitrais::util::TextBuffer Mitrais::util::WebCrawler::getContent(std::string strURL_)
{
	Mitrais::util::TextBuffer buf;
	boost::system::error_code ec;
	boost::asio::io_service io_service;

	try
	{
		urdl::read_stream stream(io_service);
		stream.open(strURL_);

		if(!stream.is_open())
		{
			ec = boost::asio::error::not_connected;
			throw boost::system::system_error(ec);
		}

		while (true) //endless loop until eof or error
		{
			char data[1024];
			std::size_t length = stream.read_some(boost::asio::buffer(data), ec);

			if (ec == boost::asio::error::eof)
			{
				break;
			}

			if (ec)
			{
				throw boost::system::system_error(ec);
			}

			string str(data);
			buf.insertContentToBuffer(data);
		}
	}
	catch (std::exception& ex)
	{
	  std::cerr << "Exception: " << ex.what() << std::endl;
	}

	return buf;
}
