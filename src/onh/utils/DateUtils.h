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

#ifndef ONH_UTILS_DATEUTILS_H_
#define ONH_UTILS_DATEUTILS_H_

#include <time.h>
#include <sys/time.h>
#include <ctime>
#include <sstream>
#include "Exception.h"

namespace onh {

/**
 * Date utils class
 */
class DateUtils {
	public:
		DateUtils();
		virtual ~DateUtils();

		/**
		 * Get current timestamp string (YYYY-MM-DD HH:MM:SS)
		 *
		 * @param addmSec Flag adding milliseconds to timestamp
		 * @param dateSep Date separator
		 * @param dateTimeSep Date and time separator
		 * @param timeSep Time separator
		 * @param milliSep Millisecond separator
		 *
		 * @return String with timestamp
		 */
		static std::string getTimestampString(bool addmSec = false,
												char dateSep = '-',
												char dateTimeSep = ' ',
												char timeSep = ':',
												char milliSep = '.');

		/**
		 * Get current timestamp struct
		 *
		 * @param milliSeconds Current Current milliseconds
		 * @param currentTimestampString Current timestamp in string
		 * @param addmSec Flag adding milliseconds to timestamp
		 * @param dateSep Date separator
		 * @param dateTimeSep Date and time separator
		 * @param timeSep Time separator
		 * @param milliSep Millisecond separator
		 *
		 * @return time_t Current timestam struct
		 */
		static std::time_t getTimestamp(int &milliSeconds,
										std::string &currentTimestampString,
										bool addmSec = false,
										char dateSep = '-',
										char dateTimeSep = ' ',
										char timeSep = ':',
										char milliSep = '.');

		/**
		 * Get current date string (YYYY-MM-DD)
		 *
		 * @param dateSep Date separator
		 * @param dateTimeSep Date and time separator
		 * @param timeSep Time separator
		 *
		 * @return String with timestamp
		 */
		static std::string getDate(char dateSep = '-');

	private:
		/**
		 * Get timestamp string from time struct
		 *
		 * @param timeInfo Pointer to the Time structure
		 * @param mSec Milliseconds value
		 * @param dateSep Date separator
		 * @param dateTimeSep Date and time separator
		 * @param timeSep Time separator
		 * @param milliSep Millisecond separator
		 * @param addmSec Flag adding milliseconds to timestamp
		 *
		 * @return String with timestamp
		 */
		static std::string getTimestampStringFromTM(struct tm* timeInfo,
													int mSec,
													bool addmSec = false,
													char dateSep = '-',
													char dateTimeSep = ' ',
													char timeSep = ':',
													char milliSep = '.');
};

}  // namespace onh

#endif  // ONH_UTILS_DATEUTILS_H_
