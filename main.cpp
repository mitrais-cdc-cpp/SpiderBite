/*
 * main.cpp
 *
 *  Created on: May 30, 2016
 *      Author: ari
 */

#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	string serverName = "www.mitrais.com";

	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service) ;
		boost::asio::ip::tcp::resolver::query query(serverName, "http");
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
				break;
			}
		}
	}
	catch(std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
	}
	return 0;
}


