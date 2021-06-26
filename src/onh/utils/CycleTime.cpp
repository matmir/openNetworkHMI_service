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

#include "CycleTime.h"

namespace onh {

CycleTime::CycleTime():
	cycle(), firstCycle(true), started(false) {
}

CycleTime::~CycleTime() {
}

void CycleTime::start() {
	if (started) {
		throw Exception("Cycle calculation already started", "CycleTime::start");
	}

	// Get start time
	cycleStart = std::chrono::steady_clock::now();
	started = true;
}

void CycleTime::stop() {
	if (!started) {
		throw Exception("Cycle calculation not started", "CycleTime::stop");
	}

	// Get stop time
	cycleStop = std::chrono::steady_clock::now();
	started = false;

	// Calculate difference
	std::chrono::duration<double, std::milli> elapsed = cycleStop-cycleStart;

	// Current cycle time (milliseconds)
	cycle.current = elapsed.count();

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

}  // namespace onh
