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

#ifndef ONH_PARSER_IPARSER_H_
#define ONH_PARSER_IPARSER_H_

#include <string>

namespace onh {

/**
 * Parser interface
 */
class IParser {
	public:
		IParser() = default;

		virtual ~IParser() = default;
		/**
		 * Parse input string and get reply
		 *
		 * @param query String with query
		 * @return String with reply
		 */
		virtual std::string getReply(const std::string& query) = 0;
};

}  // namespace onh

#endif  // ONH_PARSER_IPARSER_H_
