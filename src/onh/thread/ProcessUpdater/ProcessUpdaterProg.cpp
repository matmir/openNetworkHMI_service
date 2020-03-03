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

ProcessUpdaterProg::ProcessUpdaterProg(const ProcessUpdaterThreadData &thData):
    ThreadProgram(thData.thController, "process", "procUpd_")
{
    // Process updater
    prUpdater = new ProcessUpdater(thData.prUpdater);

    // Create delay
    itsDelay = new Delay(thData.updateInterval);
}

ProcessUpdaterProg::~ProcessUpdaterProg()
{
    if (prUpdater)
        delete prUpdater;

    if (itsDelay)
        delete itsDelay;
}

void ProcessUpdaterProg::run()
{
    try {

    	getLogger().write("Start main loop");

        if (!prUpdater)
            throw DriverException("No updater object!");

        while(!getThreadController().getExitController().exitThread()) {

            // Start thread cycle time measure
            startCycleMeasure();

            // Read data from controller
            prUpdater->update();

            // Wait
            itsDelay->wait();

            // Stop thread cycle time measure
            stopCycleMeasure();

            // Send cycle time to thread manager
            getThreadController().getCycleController().setCycleTime(getCycleTime());
        }

    } catch (Exception &e) {

    	getLogger().write(e.what());

        // Exit application
        getThreadController().getExitController().exit("Process Updater");

    }
}
