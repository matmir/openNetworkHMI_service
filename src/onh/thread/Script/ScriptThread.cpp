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

#include "ScriptThread.h"

using namespace onh;

void* script_thread(void* data) {

    // Initialize thread data
    ScriptThreadData *thDT;
    thDT = (ScriptThreadData *) data;

    // Script system
    ThreadProgram *Script = new ScriptProg(*thDT);

    // Run thread program
    Script->run();

    // Remove program
    delete Script;

    pthread_exit(NULL);
}
