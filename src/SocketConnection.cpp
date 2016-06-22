#include "../inc/SocketConnection.h"

namespace Mitrais
{
namespace util
{

/**
 * Constructor
 */

SocketConnection::SocketConnection()
{

}

/**
 * Constructor
 *
 * @serverName: the server name
 */

SocketConnection::SocketConnection(std::string serverName) :
		_serverName(serverName)
{

}

/**
 * destructor
 */

SocketConnection::~SocketConnection()
{

}

void SocketConnection::setServerName(std::string serverName)
{
	_serverName = serverName;
}

/**
 * check the socket connection
 *
 */
bool SocketConnection::isSocketOpen()
{
	bool result;
	try
	{
		// is a must to create the io service
		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		boost::asio::ip::tcp::resolver resolver(io_service) ;
		boost::asio::ip::tcp::resolver::query query(_serverName, "http");
		boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
		boost::asio::ip::tcp::resolver::iterator end;
		boost::asio::ip::tcp::endpoint endpoint;
		boost::asio::ip::tcp::socket socket(io_service);

		boost::system::error_code error = boost::asio::error::host_not_found;

		while (error && iter != end)
		{
			socket.close();
			socket.connect(*iter++, error);

			if(socket.is_open())
			{
				cout << "socket is open" << endl;
				result = true;
				break;
			}
		}
	}
	catch(std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
		result = false;
	}

	return result;
}

/**
 * check the socket connection
 *
 * @serverName : the server name
 *
 * Example : servername = www.google.com
 *
 */

bool SocketConnection::isSocketOpen(std::string serverName)
{
	setServerName(serverName);

	return isSocketOpen();
}

}}/* namespace Mitrais::util */



