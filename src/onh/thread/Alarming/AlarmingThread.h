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

#ifndef ALARMINGTHREAD_H_INCLUDED
#define ALARMINGTHREAD_H_INCLUDED

#include "AlarmingProg.h"
#include "AlarmingThreadData.h"

/**
 * Alarm system thread function
 *
 * @param data Common data (main process and thread)
 */
void* alarming_thread(void*data);

#endif // ALARMINGTHREAD_H_INCLUDED