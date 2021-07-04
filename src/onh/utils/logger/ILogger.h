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

#ifndef ONH_UTILS_LOGGER_ILOGGER_H_
#define ONH_UTILS_LOGGER_ILOGGER_H_

#include <sstream>

namespace onh {

#define LOG_INFO(val) 											\
	[&](const std::string& fn) {								\
		std::stringstream ss;									\
		ss << " INFO [" << fn << "] " << val;					\
		return ss.str();										\
	}(__FUNCTION__)

#define LOG_ERROR(val) 											\
	[&](const std::string& fn) {								\
		std::stringstream ss;									\
		ss << " ERROR [" << fn << "] " << val;					\
		return ss.str();										\
	}(__FUNCTION__)

/**
 * Logger interface
 */
class ILogger {
	public:
		/**
		 * Write to the log file
		 *
		 * @param log String with information to write
		 */
		virtual void write(const std::string& log) = 0;

		/**
		 * Write operator (Write to the log file)
		 *
		 * @param log String with information to write
		 */
		virtual void operator<<(const std::string& log) = 0;
};

}  // namespace onh

#endif  // ONH_UTILS_LOGGER_ILOGGER_H_
