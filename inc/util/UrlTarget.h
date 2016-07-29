#ifndef SPIDERBITE_INC_URLTARGET_H_
#define SPIDERBITE_INC_URLTARGET_H_

#include <iostream>
#include <string>
#include <vector>

#include "UrlTargetStatus.h"
#include "UrlTargetProtocol.h"

namespace Mitrais {
namespace util {

/**
 * Structure to hold a valid URL address and related properties
 */
struct UrlTarget
{

	std::string Url;					// valid URL address as string
	std::string Content;				// crawled content
	int Deepness = 0;

	UrlTargetProtocol Protocol;     	// protocol type (http, https, ftp)
	UrlTargetStatus Status;				// current status of crawling process for URL address

	std::vector<UrlTarget> SubUrlList; //sublist of URL withing content

	/**
	 * Get current URL
	 * @return URL
	 */
	const std::string& getUrl()
	{
		return Url;
	}

};

} /* namespace util */
} /* namespace Mitrais */

#endif /* SPIDERBITE_INC_URLTARGET_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
