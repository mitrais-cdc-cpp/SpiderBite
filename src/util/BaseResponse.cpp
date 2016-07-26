#include "../../inc/util/BaseResponse.h"

namespace Mitrais
{
namespace util
{

BaseResponse::BaseResponse() : _status(false)
{

}

BaseResponse::~BaseResponse()
{

}

void BaseResponse::addMessage(std::string message)
{
	_messages.push_back(message);
}

void BaseResponse::addSuccessMessage()
{
	if (_messages.size() > 0)
	{
		clearMessages();
	}

	_messages.push_back("Success");
}

std::vector<std::string>BaseResponse::getMessages()
{
	return _messages;
}

void BaseResponse::clearMessages()
{
	_messages.clear();
}

bool BaseResponse::getStatus()
{
	return _status;
}

void BaseResponse::updateStatus(bool status)
{
	_status = status;
}

} /* namespace util */
} /* namespace Mitrais */
