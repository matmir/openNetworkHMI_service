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

#include "ThreadProgram.h"
#include "../utils/Exception.h"

using namespace onh;

ThreadProgram::ThreadProgram(const ThreadExitController &thEC,
		const ThreadCycleContainerController & thCCC,
		const std::string& dirName,
		const std::string& fPrefix)
{
    // Thread exit controller
	thExitControll = new ThreadExitController(thEC);

	// Thread cycle time controller
	thCycleTimeControll = new ThreadCycleContainerController(thCCC);

    // Create logger
    log = new Logger(dirName, fPrefix);
    log->write("Initialize thread logger");

    // Create cycle time
    thCycle = new CycleTime();
}

ThreadProgram::~ThreadProgram()
{
    if (thExitControll)
        delete thExitControll;

    if (thCycleTimeControll)
    	delete thCycleTimeControll;

    if (thCycle)
        delete thCycle;

    if (log) {
        log->write("Closing thread logger");

        delete log;
    }
}

void ThreadProgram::startCycleMeasure() {

    if (!thCycle)
        throw Exception("Cycle time object does not exist", "ThreadProgram::startCycleMeasure");

    thCycle->start();
}

void ThreadProgram::stopCycleMeasure() {

    if (!thCycle)
        throw Exception("Cycle time object does not exist", "ThreadProgram::stopCycleMeasure");

    if (!thCycleTimeControll)
		throw Exception("Thread cycle time controller object does not exist", "ThreadProgram::stopCycleMeasure");

    thCycle->stop();

    // Pass counted value to the cycle time controller
    thCycleTimeControll->setCycleTime(thCycle->getCycle());
}

bool ThreadProgram::isExitFlag() const {

	if (!thExitControll)
		throw Exception("Thread exit controller object does not exist", "ThreadProgram::isExitFlag");

	return thExitControll->exitThread();
}

void ThreadProgram::exit(const std::string& info) {

	if (!thExitControll)
		throw Exception("Thread exit controller object does not exist", "ThreadProgram::exit");

	// Trigger application exit
	thExitControll->exit(info);
}

Logger& ThreadProgram::getLogger() {

	if (!log)
		throw Exception("Logger object does not exist", "ThreadProgram::getLogger");

	return *log;
}
