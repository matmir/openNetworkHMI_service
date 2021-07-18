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

#ifndef ONH_THREAD_TAGLOGGER_TAGLOGGERWRITERPROG_H_
#define ONH_THREAD_TAGLOGGER_TAGLOGGERWRITERPROG_H_

#include "../../driver/ProcessReader.h"
#include "../../utils/Delay.h"
#include "../../db/objs/TagLoggerItem.h"
#include "../../db/TagLoggerDB.h"
#include "../ThreadProgram.h"
#include "TagLoggerBufferController.h"

namespace onh {

/**
 * Tag logger writer program class
 */
class TagLoggerWriterProg: public ThreadProgram {
	public:
		/**
		 * Constructor
		 *
		 * @param tldb Tag logger DB
		 * @param tlbc Tag logger buffer controller
		 * @param updateInterval Logger update interval (milliseconds)
		 * @param gdcTED Thread exit data controller
		 * @param gdcCTD Thread cycle time controller
		 */
		TagLoggerWriterProg(const TagLoggerDB& tldb,
							const TagLoggerBufferController& tlbc,
							unsigned int updateInterval,
							const GuardDataController<ThreadExitData> &gdcTED,
							const GuardDataController<CycleTimeData> &gdcCTD);

		/**
		 * Copy constructor - inactive
		 */
		TagLoggerWriterProg(const TagLoggerWriterProg&) = delete;

		~TagLoggerWriterProg() override;

		/**
		 * Thread program function
		 */
		void operator()() override;

		/**
		 * Assignment operator - inactive
		 */
		TagLoggerWriterProg& operator=(const TagLoggerWriterProg&) = delete;

	private:
		/// Tag Logger DB access
		std::unique_ptr<TagLoggerDB> db;

		/// Tag logger buffer controller
		std::unique_ptr<TagLoggerBufferController> tagLoggerBuffer;

		/**
		 * Get information that tag logger writer should stop working
		 *
		 * @return True if tag logger writer should stop working
		 */
		bool exitWriterProg();

		/**
		 * Write data from buffer to DB
		 */
		void writeDataToDB();
};

}  // namespace onh

#endif  // ONH_THREAD_TAGLOGGER_TAGLOGGERWRITERPROG_H_
