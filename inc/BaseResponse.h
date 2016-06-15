#ifndef SPIDERBITE_INC_BASERESPONSE_H_
#define SPIDERBITE_INC_BASERESPONSE_H_

#include <iostream>
#include <string>
#include <vector>

namespace Mitrais {
namespace util {

class BaseResponse {
public:
	BaseResponse();
	~BaseResponse();

	void addMessage(std::string string);
	void addSuccessMessage();
	std::vector<std::string> getMessages();
	void clearMessages();
	bool getStatus();
	void updateStatus(bool status);

private:
	std::vector<std::string> _messages;
	bool _status;
};

} /* namespace util */
} /* namespace Mitrais */

#endif /* SPIDERBITE_INC_BASERESPONSE_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
