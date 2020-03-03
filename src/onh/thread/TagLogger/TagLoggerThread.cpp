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

#include "TagLoggerThread.h"

using namespace onh;

void* tagLogger_thread(void*data) {

    // Initialize thread data
    TagLoggerThreadData *thDT;
    thDT = (TagLoggerThreadData *) data;

    // Tag logger
    ThreadProgram *tagLogger = new TagLoggerProg(*thDT);

    // Run thread program
    tagLogger->run();

    // Remove program
    delete tagLogger;

    pthread_exit(NULL);
}
