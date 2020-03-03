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

#include "ThreadExit.h"

using namespace onh;

ThreadExit::ThreadExit():
    exitFromMain(false), exitFromThread(false), additionalInfo(""), socketFD(0)
{
}

ThreadExit::~ThreadExit()
{
}

void ThreadExit::exit() {

    teLock.lock();

    exitFromMain = true;
	additionalInfo = "Main process";

	teLock.unlock();
}

std::string ThreadExit::getExitInfo() {

    std::string s;

    teLock.lock();

    s = additionalInfo;

	teLock.unlock();

	return s;
}

ThreadExitController ThreadExit::getExitController() {

    return ThreadExitController(teLock.getAccess(), &exitFromMain, &exitFromThread, &additionalInfo, &socketFD);
}

int ThreadExit::getSocketFD() {

	int fd = 0;

	teLock.lock();

	fd = socketFD;

	teLock.unlock();

	return fd;
}
