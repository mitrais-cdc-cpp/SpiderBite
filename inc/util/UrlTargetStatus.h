#ifndef SPIDERBITE_INC_URLTARGETSTATUS_H_
#define SPIDERBITE_INC_URLTARGETSTATUS_H_

namespace Mitrais {
namespace util {

/**
 * Enumeration to show the status of the
 * crawling process for a given URL address
 */
enum UrlTargerStatus {
	NONE,    //!< NONE
	START,   //!< START
	CRAWLING,//!< CRAWLING
	PAUSE,   //!< PAUSE
	STOP,    //!< STOP
	DONE     //!< DONE
};

} /* namespace util */
} /* namespace Mitrais */

#endif /* SPIDERBITE_INC_URLTARGETSTATUS_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
