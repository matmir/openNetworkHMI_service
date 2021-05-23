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

#ifndef ONH_DRIVER_PROCESSREADER_H_
#define ONH_DRIVER_PROCESSREADER_H_

#include <vector>
#include <map>
#include "ProcessUtils.h"
#include "../db/objs/Tag.h"
#include "DriverProcessReader.h"

namespace onh {

/// Forward declaration
class DriverManager;

/**
 * Process reader class
 */
class ProcessReader {
	public:
		friend class DriverManager;

		/**
		 * Copy constructor
		 *
		 * @param pr ProcessReader to copy
		 */
		ProcessReader(const ProcessReader &pr);

		virtual ~ProcessReader();

		/**
		 * Assign operator - inactive
		 */
		ProcessReader& operator=(const ProcessReader&) = delete;

		/**
		 * Read bit from the process data
		 *
		 * @param tg Tag object
		 *
		 * @return Bit value
		 */
		bool getBitValue(const Tag& tg);

		/**
		 * Read bits from the process data
		 *
		 * @param tags Tags vector
		 *
		 * @return Vector with bits value
		 */
		std::vector<bool> getBitsValue(const std::vector<Tag>& tags);

		/**
		 * Read byte from the process data
		 *
		 * @param tg Tag object
		 *
		 * @return Byte value
		 */
		BYTE getByte(const Tag& tg);

		/**
		 * Read word from the process data
		 *
		 * @param tg Tag object
		 *
		 * @return Word value
		 */
		WORD getWord(const Tag& tg);

		/**
		 * Read double word from the process data
		 *
		 * @param tg Tag object
		 *
		 * @return Double word value
		 */
		DWORD getDWord(const Tag& tg);

		/**
		 * Read int from the process data
		 *
		 * @param tg Tag object
		 *
		 * @return Int value
		 */
		int getInt(const Tag& tg);

		/**
		 * Read float from the process data
		 *
		 * @param tg Tag object
		 *
		 * @return float value
		 */
		float getReal(const Tag& tg);

		/**
		 * Update reader process data (copy from driver)
		 */
		void updateProcessData();

	private:
		/**
		 * Constructor (allowed only from DriverManager)
		 */
		ProcessReader();

		/**
		 * Add Driver process reader to process reader (allowed only from DriverManager)
		 *
		 * @param id Driver process reader identifier
		 * @param dpr Driver process reader
		 */
		void addReader(unsigned int id, DriverProcessReader *dpr);

		/// Driver process data reader
		std::map<unsigned int, DriverProcessReader*> driverReader;
};

}  // namespace onh

#endif  // ONH_DRIVER_PROCESSREADER_H_
