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

#include "SocketException.h"
#include <sstream>

using namespace onh;

SocketException::SocketException():
	Exception()
{
}

SocketException::SocketException(const std::string& desc):
    Exception(desc)
{
}

SocketException::SocketException(const std::string& desc, const std::string& fName):
    Exception(desc, fName)
{
}

SocketException::SocketException(const std::string& desc, int errorNumber, const std::string& fName):
    Exception(desc, fName)
{
	std::stringstream s;

	s << allMessage;

	// Update error message on errno value
	s << " - Errno value: " << errorNumber;

	allMessage = s.str();
}

SocketException::~SocketException() {
}

