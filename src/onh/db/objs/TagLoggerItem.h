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

#ifndef ONH_DB_OBJS_TAGLOGGERITEM_H_
#define ONH_DB_OBJS_TAGLOGGERITEM_H_

#include <time.h>
#include <sys/time.h>
#include <ctime>
#include "Tag.h"

namespace onh {

/**
 * Tag logger item class
 */
class TagLoggerItem {
	public:
		/**
		 * Tag logger intervals definition
		 */
		typedef enum {
			I_100MS = 1,
			I_200MS = 2,
			I_500MS = 3,
			I_1S = 4,
			I_XS = 5,
			I_ON_CHANGE = 6,
		} intervals;

		/**
		 * Tag logger timestamp and value structure
		 */
		typedef struct {
			/// Value timestamp
			std::string timestamp;

			/// Tag value
			std::string value;
		} timeVal;

		TagLoggerItem();

		/**
		 * Tag logger item constructor
		 *
		 * @param id Tag logger identifier
		 * @param tag Tag object
		 * @param interval Tag update interval
		 * @param intervalSec Tag update interval in seconds
		 * @param lastUpdate Tag last update timestamp string (YYYY-MM-DD HH:MM:SS.MSS)
		 * @param lastValue Tag last value
		 * @param enable Tag logger enable flag
		 */
		TagLoggerItem(unsigned int id,
						const Tag& tag,
						intervals interval,
						unsigned int intervalSec,
						const std::string& lastUpdate,
						const std::string& lastValue,
						bool enable);

		/**
		 * Copy constructor - default
		 */
		TagLoggerItem(const TagLoggerItem&) = default;

		virtual ~TagLoggerItem();

		/**
		 * Assign operator - default
		 */
		TagLoggerItem& operator=(const TagLoggerItem&) = default;

		/**
		 * Get Tag logger identifier
		 *
		 * @return Tag logger id
		 */
		unsigned int getId() const;

		/**
		 * Set Tag logger identifier
		 *
		 * @param id Tag logger identifier
		 */
		void setId(unsigned int id);

		/**
		 * Get Tag object
		 *
		 * @return Tag object
		 */
		const Tag& getTag() const;

		/**
		 * Set Tag object
		 *
		 * @param tag Tag object
		 */
		void setTag(const Tag& tag);

		/**
		 * Get Tag update interval
		 *
		 * @return Tag update interval
		 */
		const intervals& getInterval() const;

		/**
		 * Set Tag update interval
		 *
		 * @param interval Tag update interval
		 */
		void setInterval(const intervals& interval);

		/**
		 * Get Tag update interval in seconds
		 *
		 * @return Tag update interval in seconds
		 */
		unsigned int getIntervalSec() const;

		/**
		 * Set Tag update interval in seconds
		 *
		 * @param intervalSec Tag update interval in seconds
		 */
		void setIntervalSec(unsigned int intervalSec);

		/**
		 * Get Tag last update timestamp in string (YYYY-MM-DD HH:MM:SS.MSS)
		 *
		 * @return Tag last update timestamp
		 */
		std::string getLastUpdate() const;

		/**
		 * Set Tag last update timestamp in string (YYYY-MM-DD HH:MM:SS.MSS)
		 *
		 * @param lastUpdate Tag last update timestamp in string
		 */
		void setLastUpdate(const std::string& lastUpdate);

		/**
		 * Get Tag last tag value
		 *
		 * @return Tag last value
		 */
		const std::string& getLastValue() const;

		/**
		 * Set Tag last value
		 *
		 * @param lastValue Tag last value
		 */
		void setLastValue(const std::string& lastValue);

		/**
		 * Get Tag current update timestamp in string (YYYY-MM-DD HH:MM:SS.MSS)
		 *
		 * @return Tag current update timestamp
		 */
		std::string getCurrentUpdate() const;

		/**
		 * Get Tag logger enable flag
		 *
		 * @return Tag logger enable flag
		 */
		bool isEnabled() const;

		/**
		 * Set Tag logger enable flag
		 *
		 * @param enable Tag logger enable flag
		 */
		void setEnable(bool enable);

		/**
		 * Check if tag need to be updated id DB
		 *
		 * @param tagValue Tag value string
		 *
		 * @return true if tag need to be updated
		 */
		bool isNeededUpdate(const std::string& tagValue);

		/**
		 * Set tag logger last value and timestamp
		 *
		 * @param tv Tag logger last timestamp and value structure
		 */
		void setLastTimeValue(const timeVal& tv);

		/**
		 * Get tag logger last value and timestamp
		 *
		 * @return Tag logger last timestamp and value structure
		 */
		timeVal getLastTimeValue() const;

		/**
		 * Get tag logger current value and timestamp
		 *
		 * @return Tag logger current timestamp and value structure
		 */
		timeVal getCurrentTimeValue() const;

	private:
		/// Tag logger identifier
		unsigned int ltid;

		/// Tag object
		Tag ltTag;

		/// Tag logger interval
		intervals ltInterval;

		/// Tag logger interval in second (used if interval is Xs)
		unsigned int ltIntervalS;

		/// Tag logger last update value
		timeVal ltLast;

		/// Tag logger current update value
		timeVal ltCurrent;

		/// Tag logger enabled
		bool ltEnable;

		/**
		 * Get tag last update timestamp (seconds from epoch)
		 *
		 * @return Tag last update timestamp
		 */
		std::time_t getTagUpdateTimestamp() const;

		/**
		 *  Get tag last update milliseconds
		 *
		 * @return Tag last update milliseconds
		 */
		int getTagUpdateMilliseconds() const;

		/**
		 * Check if tag need to be updated (millisecond difference)
		 *
		 * @param dTS Timestamp difference (seconds)
		 * @param tagMillisec Tag last update milliseconds
		 * @param currentMillisec Current time milliseconds
		 * @param msFactor Difference between current MS and tag MS which trigger update
		 *
		 * @return  True if tag need to be updated
		 */
		bool msUpdate(double dTS, unsigned int tagMillisec, unsigned int currentMillisec, unsigned int msFactor) const;

		/**
		 * Check identifier
		 *
		 * @param id Identifier
		 */
		void checkId(unsigned int id) const;

		/**
		 * Check intervals
		 *
		 * @param interval Interval
		 */
		void checkInterval(const intervals& interval) const;

		/**
		 * Check last update value
		 *
		 * @param lastUpdate Last update value
		 */
		void checkLastUpdate(const std::string& lastUpdate) const;

		/**
		 * Check last value
		 *
		 * @param lastUpdate Last update value
		 */
		void checkLastValue(const std::string& value) const;
};

}  // namespace onh

#endif  // ONH_DB_OBJS_TAGLOGGERITEM_H_
