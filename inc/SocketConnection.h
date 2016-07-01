#ifndef INC_SOCKETCONNECTION_H_
#define INC_SOCKETCONNECTION_H_

#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>

#include "Logger.h"

using namespace std;

namespace Mitrais
{
namespace util
{

class SocketConnection
{
public:

	SocketConnection();
	SocketConnection(std::string serverName);
	~SocketConnection();

	void setServerName(std::string serverName);
	bool isSocketOpen();
	bool isSocketOpen(std::string serverName);
private:
	std::string _serverName;
};

}
} //namespace Mitrais::util



#endif /* INC_SOCKETCONNECTION_H_ */
