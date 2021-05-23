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

#ifndef ONH_THREAD_TAGLOGGER_TAGLOGGERBUFFERCONTROLLER_H_
#define ONH_THREAD_TAGLOGGER_TAGLOGGERBUFFERCONTROLLER_H_

#include <vector>
#include "../../utils/MutexAccess.h"
#include "../../db/objs/TagLoggerItem.h"
#include "../../utils/GuardDataController.h"

namespace onh {

/// Forward declaration
class TagLoggerBufferContainer;

/// Guarded Tag logger buffer controller
typedef GuardDataController<std::vector<TagLoggerItem>> loggerBufferController;

/**
 * Tag logger buffer controller class
 */
class TagLoggerBufferController {
	public:
		friend class TagLoggerBufferContainer;

		/**
		 * Copy constructor
		 *
		 * @param tlbc Tag logger buffer controller object to copy
		 */
		TagLoggerBufferController(const TagLoggerBufferController& tlbc);

		virtual ~TagLoggerBufferController();

		/**
		 * Assign operator - inactive
		 */
		TagLoggerBufferController& operator=(const TagLoggerBufferController&) = delete;

		/**
		 * Insert new data into the buffer
		 *
		 * @param data Data to insert
		 */
		void putData(const std::vector<TagLoggerItem> &data);

		/**
		 * Copy data from buffer to the input vector
		 *
		 * @param data Input vector on data
		 */
		void getData(std::vector<TagLoggerItem> &data);

		/**
		 * Check if buffer is empty
		 *
		 * @return True if buffer is empty
		 */
		bool isEmpty();

		/**
		 * Set finish flag
		 */
		void setFinished();

		/**
		 * Check if finish flag is set
		 *
		 * @return Finish flag
		 */
		bool isFinished();

	private:
		/**
		 * Constructor (allowed only from TagLoggerBufferContainer)
		 *
		 * @param lbc Data buffer controller
		 * @param gdcf Finish flag controller
		 * @param readOnlyFlag Read only flag
		 */
		TagLoggerBufferController(const loggerBufferController &lbc,
									const GuardDataController<bool> &gdcf,
									bool readOnlyFlag = false);

		/// Data buffer controller
		loggerBufferController buff;

		/// Flag informs that controller finished inserting data
		GuardDataController<bool> controllerInsertFinished;

		/// Read only flag
		bool readOnly;
};

}  // namespace onh

#endif  // ONH_THREAD_TAGLOGGER_TAGLOGGERBUFFERCONTROLLER_H_
