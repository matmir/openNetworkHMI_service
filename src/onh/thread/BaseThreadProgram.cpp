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

#include "BaseThreadProgram.h"
#include "../utils/Exception.h"

namespace onh {

BaseThreadProgram::BaseThreadProgram(const GuardDataController<ThreadExitData> &gdcTED,
									const std::string& dirName,
									const std::string& fPrefix,
									bool printLogMsg):
	printMsg(printLogMsg),
	thExitController(gdcTED),
	log(std::make_unique<TextLogger>(dirName, fPrefix)) {
	// Create info
	if (printMsg)
		log->write(LOG_INFO("Initialize thread logger"));
}

BaseThreadProgram::~BaseThreadProgram() {
	if (printMsg)
		log->write(LOG_INFO("Closing thread logger"));
}

const GuardDataController<ThreadExitData>& BaseThreadProgram::getExitController() const {
	return thExitController;
}

bool BaseThreadProgram::isExitFlag() {
	ThreadExitData ex;
	thExitController.getData(ex);

	return ex.exit;
}

void BaseThreadProgram::exit(const std::string& info) {
	ThreadExitData ex;
	ex.exit = true;
	ex.additionalInfo = info;

	// Trigger application exit
	thExitController.setData(ex);
}

ILogger& BaseThreadProgram::getLogger() {
	return *log;
}

}  // namespace onh
