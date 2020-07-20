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

#include "TagException.h"

using namespace onh;

TagException::TagException():
    Exception(), exType(NONE)
{
}

TagException::TagException(ExceptionType type, const std::string& desc, const std::string& fName):
    Exception(desc, fName), exType(type)
{
}

TagException::~TagException() noexcept
{
}

TagException::ExceptionType TagException::getType() const {

    return exType;
}
