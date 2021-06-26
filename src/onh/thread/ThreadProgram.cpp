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
	BaseThreadProgram(gdcTED, dirName, fPrefix), thDelay(updateInterval), thCycleTimeController(gdcCTD) {
}

ThreadProgram::~ThreadProgram() {
}

void ThreadProgram::startCycleMeasure() {
	thCycle.start();
}

void ThreadProgram::stopCycleMeasure() {
	thCycle.stop();

	// Pass counted value to the cycle time controller
	thCycleTimeController.setData(thCycle.getCycle());
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
