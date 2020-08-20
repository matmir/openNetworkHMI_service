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

#include "DriverPollingProg.h"

#include <stdlib.h>
#include <sstream>
#include "../../driver/DriverException.h"
#include "../../utils/Exception.h"

using namespace onh;

DriverPollingProg::DriverPollingProg(const DriverBufferUpdater& dbu,
										unsigned int updateInterval,
										const GuardDataController<ThreadExitData> &gdcTED,
										const GuardDataController<CycleTimeData> &gdcCTD):
    ThreadProgram(gdcTED, gdcCTD, "driver", "polling_")
{
    // Driver updater
    drvUpdater = new DriverBufferUpdater(dbu);

    // Create delay
    itsDelay = new Delay(updateInterval);
}

DriverPollingProg::~DriverPollingProg()
{
    if (drvUpdater)
        delete drvUpdater;

    if (itsDelay)
        delete itsDelay;
}


void DriverPollingProg::operator()() {

    try {

    	getLogger().write("Start main loop");

        if (!drvUpdater)
            throw Exception("No driver updater object");

        while(!isExitFlag()) {

            // Start thread cycle time measure
            startCycleMeasure();

            // Read data from controller to buffer
            drvUpdater->update();

            // Wait
            itsDelay->wait();

            // Stop thread cycle time measure
            stopCycleMeasure();
        }

    } catch (Exception &e) {

    	getLogger().write(e.what());

        // Exit application
    	exit("Driver polling");
    }
}
