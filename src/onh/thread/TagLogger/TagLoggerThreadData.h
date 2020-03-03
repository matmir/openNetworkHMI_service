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

#ifndef TAGLOGGERTHREADDATA_H_INCLUDED
#define TAGLOGGERTHREADDATA_H_INCLUDED

#include "../../driver/ProcessReader.h"
#include "../ThreadController.h"
#include "../../db/TagLoggerDB.h"
#include "TagLoggerBufferController.h"

namespace onh {

    /**
	 * Tag logger thread data structure
	 */
	typedef struct {
	    /// Process data reader
		ProcessReader prReader;

        /// Thread controller
		ThreadController thController;

		/// Tag logger DB
		TagLoggerDB db;

		/// Tag logger buffer controller
		TagLoggerBufferController loggerBufferController;

		/// Logger update interval (milliseconds)
		unsigned int updateInterval;
	} TagLoggerThreadData;

}

#endif // TAGLOGGERTHREADDATA_H_INCLUDED
