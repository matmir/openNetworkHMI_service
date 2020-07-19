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

#include "ThreadCycleContainerController.h"

using namespace onh;

ThreadCycleContainerController::ThreadCycleContainerController(const ThreadCycleContainerController& tccc):
    maLock(tccc.maLock), pCycle(tccc.pCycle), readOnly(tccc.readOnly)
{
}

ThreadCycleContainerController::ThreadCycleContainerController(const MutexAccess &mal, CycleTimeData *pThCycleData, bool readOnlyFlag):
    maLock(mal), pCycle(pThCycleData), readOnly(readOnlyFlag)
{
}

ThreadCycleContainerController::~ThreadCycleContainerController()
{
}

void ThreadCycleContainerController::setCycleTime(const CycleTimeData &cycleData) {

    if (readOnly)
        throw Exception("Cycle Container Controller is in read only state", "ThreadCycleContainerController::setCycleTime");

    if (!pCycle)
        throw Exception("CycleTimeData not initialized", "ThreadCycleContainerController::setCycleTime");

    maLock.lock();

    (*pCycle).current = cycleData.current;
    (*pCycle).max = cycleData.max;
    (*pCycle).min = cycleData.min;

    maLock.unlock();
}

CycleTimeData ThreadCycleContainerController::getCycleTime() {

    if (!pCycle)
        throw Exception("CycleTimeData not initialized", "ThreadCycleContainerController::getCycleTime");

    CycleTimeData ret = {0.0, 0.0, 0.0};

    maLock.lock();

    ret.current = (*pCycle).current;
    ret.max = (*pCycle).max;
    ret.min = (*pCycle).min;

    maLock.unlock();

    return ret;
}
