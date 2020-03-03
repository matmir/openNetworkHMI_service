/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2020 Mateusz Mirosławski.
 *
 * openNetworkHMI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * openNetworkHMI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with openNetworkHMI.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SRC_ONH_THREAD_TAGLOGGER_TAGLOGGERBUFFERCONTAINER_H_
#define SRC_ONH_THREAD_TAGLOGGER_TAGLOGGERBUFFERCONTAINER_H_

#include <vector>
#include "../../utils/MutexContainer.h"
#include "../../db/objs/TagLoggerItem.h"
#include "TagLoggerBufferController.h"

namespace onh {

	/**
	 * Tag logger buffer controller class
	 */
	class TagLoggerBufferContainer {

		public:

			TagLoggerBufferContainer();

			virtual ~TagLoggerBufferContainer();

			/**
			 * Get tag logger buffer container controller object
			 *
			 * @param readOnly Read only flag
			 *
			 * @return Tag logger buffer container controller object
			 */
			TagLoggerBufferController getController(bool readOnly = false);

		private:
			/**
			 * Copy constructor
			 */
			TagLoggerBufferContainer(const TagLoggerBufferContainer&) {};

			/**
			 * Assign operator
			 */
			void operator=(const TagLoggerBufferContainer&) {};

			/// Mutex for protecting buffer
			MutexContainer buffLock;

			/// Data buffer
			std::vector<TagLoggerItem> buff;

			/// Mutex for protecting finish flag
			MutexContainer finishLock;

			/// Flag informs that controller finished inserting data
			bool controllerInsertFinished;
	};
}

#endif /* SRC_ONH_THREAD_TAGLOGGER_TAGLOGGERBUFFERCONTAINER_H_ */
