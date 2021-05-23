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

#include "modbusexception.h"

namespace modbusM {

ModbusException::ModbusException():
	errorMessage(""), functionName(""), allMessage("none") {
}

ModbusException::ModbusException(const std::string& exceptionMSG):
	errorMessage(exceptionMSG), functionName(""), allMessage(exceptionMSG) {
}

ModbusException::ModbusException(const std::string& exceptionMSG,
									const std::string& funcName):
	errorMessage(exceptionMSG), functionName(funcName) {
	allMessage = functionName + ": ";
	allMessage += errorMessage;
}

ModbusException::~ModbusException() noexcept {
}

const char* ModbusException::what() const noexcept {
	return allMessage.c_str();
}

}  // namespace modbusM
