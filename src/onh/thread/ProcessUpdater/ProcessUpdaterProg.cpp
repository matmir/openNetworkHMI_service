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

#include "ProcessUpdaterProg.h"

#include <stdlib.h>
#include <sstream>
#include "../../utils/Exception.h"

using namespace onh;

ProcessUpdaterProg::ProcessUpdaterProg(const ProcessUpdater& pru,
										unsigned int updateInterval,
										const ThreadExitController &thEC,
										const GuardDataController<CycleTimeData> &gdcCTD):
	ThreadProgram(thEC, gdcCTD, "process", "procUpd_")
{
    // Process updater
    prUpdater = new ProcessUpdater(pru);

    // Create delay
    itsDelay = new Delay(updateInterval);
}

ProcessUpdaterProg::~ProcessUpdaterProg()
{
    if (prUpdater)
        delete prUpdater;

    if (itsDelay)
        delete itsDelay;
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
            itsDelay->wait();

            // Stop thread cycle time measure
            stopCycleMeasure();
        }

    } catch (Exception &e) {

    	getLogger().write(e.what());

        // Exit application
        exit("Process Updater");

    }
}
