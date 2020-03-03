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

#ifndef PROCESSUPDATERTHREAD_H_INCLUDED
#define PROCESSUPDATERTHREAD_H_INCLUDED

#include "ProcessUpdaterProg.h"
#include "ProcessUpdaterThreadData.h"

/**
 * Process update thread function
 *
 * @param data Common data (main process and thread)
 */
void* processUpdater_thread(void* data);

#endif // PROCESSUPDATERTHREAD_H_INCLUDED
