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

#ifndef ONH_THREAD_TAGLOGGER_TAGLOGGERPROG_H_
#define ONH_THREAD_TAGLOGGER_TAGLOGGERPROG_H_

#include <map>
#include "../../driver/ProcessReader.h"
#include "../../utils/Delay.h"
#include "../../db/objs/TagLoggerItem.h"
#include "../../db/TagLoggerDB.h"
#include "../ThreadProgram.h"
#include "TagLoggerBufferController.h"

namespace onh {

/**
 * Tag logger program class
 */
class TagLoggerProg: public ThreadProgram {
	public:
		/**
		 * Constructor
		 *
		 * @param pr Process reader
		 * @param tldb Tag logger DB
		 * @param tlbc Tag logger buffer controller
		 * @param updateInterval Logger update interval (milliseconds)
		 * @param gdcTED Thread exit data controller
		 * @param gdcCTD Thread cycle time controller
		 */
		TagLoggerProg(const ProcessReader& pr,
						const TagLoggerDB& tldb,
						const TagLoggerBufferController& tlbc,
						unsigned int updateInterval,
						const GuardDataController<ThreadExitData> &gdcTED,
						const GuardDataController<CycleTimeData> &gdcCTD);

		/**
		 * Copy constructor - inactive
		 */
		TagLoggerProg(const TagLoggerProg&) = delete;

		~TagLoggerProg() override;

		/**
		 * Thread program function
		 */
		void operator()() override;

		/**
		 * Assignment operator - inactive
		 */
		TagLoggerProg& operator=(const TagLoggerProg&) = delete;

	private:
		/// Handle for process reader object
		std::unique_ptr<ProcessReader> prReader;

		/// Tag Logger DB access
		std::unique_ptr<TagLoggerDB> db;

		/// Tag logger buffer controller
		std::unique_ptr<TagLoggerBufferController> tagLoggerBuffer;

		/**
		 * Tag logger last values
		 */
		std::map<unsigned int, TagLoggerItem::timeVal> loggerLastValue;

		/**
		 * Update tags
		 */
		void updateTags();

		/**
		 * Store logger last value
		 *
		 * @param tagLog Tag logger item
		 */
		void storeLastValue(const TagLoggerItem& tagLog);

		/**
		 * Initialize tag logger last value
		 *
		 * @param tagLog Tag logger item
		 */
		void initLoggerLastValue(TagLoggerItem& tagLog);
};

}  // namespace onh

#endif  // ONH_THREAD_TAGLOGGER_TAGLOGGERPROG_H_
