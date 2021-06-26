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

#include "ProcessUpdaterProg.h"

#include <stdlib.h>
#include <sstream>
#include "../../utils/Exception.h"

namespace onh {

ProcessUpdaterProg::ProcessUpdaterProg(const ProcessUpdater& pru,
										unsigned int connId,
										unsigned int updateInterval,
										const GuardDataController<ThreadExitData> &gdcTED,
										const GuardDataController<CycleTimeData> &gdcCTD):
	ThreadProgram(gdcTED, gdcCTD, updateInterval, "process", "procUpd_"+std::to_string(connId)+"_"),
	prUpdater(std::make_unique<ProcessUpdater>(pru)) {
}

ProcessUpdaterProg::~ProcessUpdaterProg() {
}

void ProcessUpdaterProg::operator()() {
	try {
		getLogger().write("Start main loop");

		if (!prUpdater)
			throw Exception("No updater object!");

		while(!isExitFlag()) {
			// Start thread cycle time measure
			startCycleMeasure();

			// Read data from controller
			prUpdater->update();

			// Wait
			threadWait();

			// Stop thread cycle time measure
			stopCycleMeasure();
		}
	} catch (Exception &e) {
		getLogger().write(e.what());

		// Exit application
		exit("Process Updater");
	}
}

}  // namespace onh
