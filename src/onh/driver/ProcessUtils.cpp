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

#include "ProcessUtils.h"
#include <sstream>

using namespace onh;

void ProcessUtils::triggerTagTypeError(const std::string& tagName, const std::string& fName) {

    std::stringstream s;
    s << "Tag: " << tagName << " has wrong type";
    throw TagException(TagException::WRONG_TYPE, s.str(), fName);
}

void ProcessUtils::triggerTagAreaError(const std::string& tagName, const std::string& fName) {

    std::stringstream s;
    s << "Tag: " << tagName << " has wrong area";
    throw TagException(TagException::WRONG_AREA, s.str(), fName);
}

void ProcessUtils::triggerError(const std::string& msg, const std::string& tagName, const std::string& fName) {

    std::stringstream s;

    if (tagName !="") {
        s << "(" << tagName << "): " << msg;
    } else {
        s << msg;
    }

    throw Exception(s.str(), fName);
}
