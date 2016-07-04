#ifndef SPIDERBITE_INC_URLTARGET_H_
#define SPIDERBITE_INC_URLTARGET_H_

#include <iostream>
#include <string>
#include <list>

#include "UrlTargetStatus.h"

namespace Mitrais {
namespace util {

/**
 * Structure to hold a valid URL address and related properties
 */
struct UrlTarget
{
	std::string Url;				// valid URL address as string
	std::string LatestUrlPosition;	// TBD
	UrlTargerStatus Status;			// current status of crawling process for URL address
	std::vector<UrlTarget> SubUrlList;
	int Deepness = 0;


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
