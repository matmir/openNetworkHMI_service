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

#include "ThreadController.h"
#include "../utils/Logger.h"
#include "../utils/Exception.h"
#include <stdlib.h>

using namespace onh;

ThreadController::ThreadController():
    thExit(0), cycleTime(0)
{
}

ThreadController::ThreadController(const ThreadController &tc) {

    // Exit controller
    thExit = new ThreadExitController(*tc.thExit);

    // Cycle time container controller (if exist)
    if (tc.cycleTime) {
        cycleTime = new ThreadCycleContainerController(*tc.cycleTime);
    } else {
        cycleTime = 0;
    }
}

ThreadController::ThreadController(const ThreadExitController &tec):
    cycleTime(0)
{
    // Exit controller
    thExit = new ThreadExitController(tec);
}

ThreadController::ThreadController(const ThreadExitController &tec, const ThreadCycleContainerController &tccc) {

    // Exit controller
    thExit = new ThreadExitController(tec);

    // Cycle time container controller
    cycleTime = new ThreadCycleContainerController(tccc);
}

ThreadController::~ThreadController()
{
    if (thExit)
        delete thExit;

    if (cycleTime)
        delete cycleTime;
}

ThreadController& ThreadController::operator=(const ThreadController &tc) {

    // Check self assignment
    if(&tc == this)
        return *this;

    // Exit controller
    if (thExit)
        delete thExit;
    thExit = new ThreadExitController(*tc.thExit);

    // Cycle time container controller
    if (cycleTime)
        delete cycleTime;

    if (tc.cycleTime) {
        cycleTime = new ThreadCycleContainerController(*tc.cycleTime);
    } else {
        cycleTime = 0;
    }

    return *this;
}

ThreadExitController& ThreadController::getExitController() {

    if (!thExit)
        throw Exception("Thread exit controller object does not exist", "ThreadController::getExitController");

    return *thExit;
}

ThreadCycleContainerController& ThreadController::getCycleController() {

    if (!cycleTime)
        throw Exception("Thread cycle container controller object does not exist", "ThreadController::getCycleController");

    return *cycleTime;
}
