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

#include "ThreadProgram.h"
#include "../utils/Exception.h"

namespace onh {

ThreadProgram::ThreadProgram(const GuardDataController<ThreadExitData> &gdcTED,
								const GuardDataController<CycleTimeData> &gdcCTD,
								unsigned int updateInterval,
								const std::string& dirName,
								const std::string& fPrefix):
	thDelay(updateInterval), thExitController(gdcTED), thCycleTimeController(gdcCTD),
	log(std::make_unique<Logger>(dirName, fPrefix)) {
	// Create info
	log->write("Initialize thread logger");
}

ThreadProgram::~ThreadProgram() {
	log->write("Closing thread logger");
}

void ThreadProgram::startCycleMeasure() {
	thCycle.start();
}

void ThreadProgram::stopCycleMeasure() {
	thCycle.stop();

	// Pass counted value to the cycle time controller
	thCycleTimeController.setData(thCycle.getCycle());
}

bool ThreadProgram::isExitFlag() {
	ThreadExitData ex;
	thExitController.getData(ex);

	return ex.exit;
}

void ThreadProgram::exit(const std::string& info) {
	ThreadExitData ex;
	ex.exit = true;
	ex.additionalInfo = info;

	// Trigger application exit
	thExitController.setData(ex);
}

Logger& ThreadProgram::getLogger() {
	return *log;
}

void ThreadProgram::threadWait() {
	thDelay.wait();
}

void ThreadProgram::threadWaitStart() {
	thDelay.startDelay();
}

void ThreadProgram::threadWaitAfterStart() {
	thDelay.waitAfterStart();
}

}  // namespace onh
