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

#ifndef SRC_ONH_THREAD_TAGLOGGER_TAGLOGGERWRITERPROG_H_
#define SRC_ONH_THREAD_TAGLOGGER_TAGLOGGERWRITERPROG_H_

#include "TagLoggerWriterThreadData.h"
#include "../../utils/Delay.h"
#include "../../db/objs/TagLoggerItem.h"
#include "../../db/TagLoggerDB.h"
#include "../ThreadProgram.h"

namespace onh {

	/**
	 * Tag logger writer program class
	 */
	class TagLoggerWriterProg: public ThreadProgram {

		public:

			/**
			 * Constructor
			 *
			 * @param thData Tag logger writer thread data structure
			 */
			TagLoggerWriterProg(const TagLoggerWriterThreadData &thData);

			virtual ~TagLoggerWriterProg();

			/**
			 * Run tag logger writer
			 */
			void run();

		private:

			/// Timer delay object
			Delay* itsDelay;

			/// Tag Logger DB access
			TagLoggerDB *db;

			/// Tag logger buffer controller
			TagLoggerBufferController *tagLoggerBuffer;

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

}

#endif /* SRC_ONH_THREAD_TAGLOGGER_TAGLOGGERWRITERPROG_H_ */
