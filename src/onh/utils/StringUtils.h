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

#ifndef ONH_UTILS_STRINGUTILS_H
#define ONH_UTILS_STRINGUTILS_H

#include <string>
#include <vector>
#include "Exception.h"

namespace onh {

    /**
	 * String utils class
	 */
    class StringUtils {

        public:
            StringUtils();
            virtual ~StringUtils();

            /**
             * Explode string into the vector
             *
             * @param str String to explode
             * @param sep Strings separator
             *
             * @return Vector with strings
             */
            static std::vector<std::string> explode(std::string str, char sep);

            /**
             * Replace char in string
             *
             * @param data String data
             * @param chs Character to replace
             * @param chr Character on which replace
             *
             * @return String data with replaced characters
             */
            static std::string replaceChar(const std::string& data, char chs, char chr);
    };

}

#endif // ONH_UTILS_STRINGUTILS_H
