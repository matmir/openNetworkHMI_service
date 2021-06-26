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

#include "StringUtils.h"
#include <sstream>

namespace onh {

StringUtils::StringUtils() {
}

StringUtils::~StringUtils() {
}

std::vector<std::string> StringUtils::explode(std::string str, char sep) {
	std::vector<std::string> v;
	std::stringstream s;

	if (str.length() == 0 || sep == 0)
		throw Exception("No data", "StringUtils::explode");

	for (unsigned int i=0; i < str.length(); ++i) {
		// Separator
		if (str[i] == sep) {
			// Push data into the vector
			v.push_back(s.str());

			// Clear string stream
			s.str("");
			s.clear();
		} else {
			// Put char into the string
			s << str[i];

			// Last char in string
			if (i == str.length()-1) {
				v.push_back(s.str());
			}
		}
	}

	return v;
}

std::string StringUtils::replaceChar(const std::string& data, char chs, char chr) {
	std::string str = data;

	if (data.length() == 0 || chs == 0 || chr == 0)
		throw Exception("No data", "StringUtils::replaceChar");

	for (unsigned int i=0; i < str.length(); ++i) {
		if (str[i] == chs) {
			str[i] = chr;
		}
	}

	return str;
}

}  // namespace onh
