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

#include "CycleTime.h"

using namespace onh;

CycleTime::CycleTime() {

    // Init cycle times
    cycle.min = 0;
    cycle.max = 0;
    cycle.current = 0;

    firstCycle = true;

    // Init time structures
    clock_gettime(CLOCK_MONOTONIC, &cycleStart);
    clock_gettime(CLOCK_MONOTONIC, &cycleStop);
}

CycleTime::~CycleTime()
{
}

void CycleTime::start() {

    // Get time
    clock_gettime(CLOCK_MONOTONIC, &cycleStart);
}

void CycleTime::stop() {

    long seconds, nseconds;
    double msec;

    // Get time
    clock_gettime(CLOCK_MONOTONIC, &cycleStop);

    // Calculate difference
    seconds  = cycleStop.tv_sec  - cycleStart.tv_sec;
    nseconds = cycleStop.tv_nsec - cycleStart.tv_nsec;
    msec = nseconds/1000000.0;

    // Current cycle time (milliseconds)
    cycle.current = ((seconds) * 1000 + msec);

    // Update max
    if (cycle.current > cycle.max) {
        cycle.max = cycle.current;
    }

    // First cycle time -> set min
    if (firstCycle) {
        cycle.min = cycle.current;
        firstCycle = false;
    }

    // Update min
    if (cycle.current < cycle.min) {
        cycle.min = cycle.current;
    }
}

CycleTimeData CycleTime::getCycle() const {

    return cycle;
}
