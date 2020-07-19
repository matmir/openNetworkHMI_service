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

#include "ThreadExitController.h"

using namespace onh;

ThreadExitController::ThreadExitController(const ThreadExitController& tec):
    maLock(tec.maLock), exitFromMain(tec.exitFromMain), exitFromThread(tec.exitFromThread), additionalInfo(tec.additionalInfo), socketFD(tec.socketFD)
{
}

ThreadExitController::ThreadExitController(const MutexAccess &mal, bool *exFromMain, bool *exFromThread, std::string *adInfo, int *sockFD):
    maLock(mal), exitFromMain(exFromMain), exitFromThread(exFromThread), additionalInfo(adInfo), socketFD(sockFD)
{
}

ThreadExitController::~ThreadExitController()
{
}

bool ThreadExitController::exitThread() {

    if (!exitFromMain || !exitFromThread)
        throw Exception("ExitController data not initialized", "ThreadExitController::exitThread");

    bool ret = false;

    maLock.lock();

    ret = (*exitFromMain || *exitFromThread) ? (true) : (false);

    maLock.unlock();

    return ret;
}

void ThreadExitController::exit(const std::string &info) {

    if (!exitFromMain || !exitFromThread)
        throw Exception("ExitController data not initialized", "ThreadExitController::exit");

    maLock.lock();

    *exitFromThread = true;
	*additionalInfo = info;

	maLock.unlock();
}

void ThreadExitController::setSocketFD(int sockFD) {

	maLock.lock();

	*socketFD = sockFD;

	maLock.unlock();
}
