/*
 * SaveModeEnum.h
 *
 *  Created on: Jul 14, 2016
 *      Author: developer
 */

#ifndef INC_SAVEMODEENUM_H_
#define INC_SAVEMODEENUM_H_

namespace Mitrais {
	namespace util {
		/**
		 * Enumeration to select which saving method
		 * user preferred to store the content
		 */
		enum SaveModeEnum {
			SAVE_TO_FILE,	//!< Save the content to a file
			SAVE_TO_DB		//!< Save the content to the database
		};

	} /* namespace util */
} /* namespace Mitrais */


#endif /* INC_SAVEMODEENUM_H_ */
