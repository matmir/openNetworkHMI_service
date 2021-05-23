/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2021 Mateusz Mirosławski.
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

#ifndef ONH_THREAD_TAGLOGGER_TAGLOGGERBUFFERCONTAINER_H_
#define ONH_THREAD_TAGLOGGER_TAGLOGGERBUFFERCONTAINER_H_

#include <vector>
#include "../../utils/MutexContainer.h"
#include "../../db/objs/TagLoggerItem.h"
#include "TagLoggerBufferController.h"
#include "../../utils/GuardDataContainer.h"

namespace onh {

/// Guarded Tag logger buffer container
typedef GuardDataContainer<std::vector<TagLoggerItem>> loggerBufferContainer;

/**
 * Tag logger buffer controller class
 */
class TagLoggerBufferContainer {
	public:
		/**
		 * Constructor
		 */
		TagLoggerBufferContainer();

		/**
		 * Copy constructor - inactive
		 */
		TagLoggerBufferContainer(const TagLoggerBufferContainer&) = delete;

		virtual ~TagLoggerBufferContainer();

		/**
		 * Assign operator - inactive
		 */
		TagLoggerBufferContainer& operator=(const TagLoggerBufferContainer&) = delete;

		/**
		 * Get tag logger buffer container controller object
		 *
		 * @param readOnly Read only flag (allowed only reading from buffer)
		 *
		 * @return Tag logger buffer container controller object
		 */
		TagLoggerBufferController getController(bool readOnly = false);

	private:
		/// Data buffer
		loggerBufferContainer buff;

		/// Flag informs that controller finished inserting data
		GuardDataContainer<bool> controllerInsertFinished;
};

}  // namespace onh

#endif  // ONH_THREAD_TAGLOGGER_TAGLOGGERBUFFERCONTAINER_H_
