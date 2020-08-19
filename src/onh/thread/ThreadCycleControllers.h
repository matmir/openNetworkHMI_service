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

#ifndef SRC_ONH_THREAD_THREADCYCLECONTROLLERS_H_
#define SRC_ONH_THREAD_THREADCYCLECONTROLLERS_H_

#include "../utils/CycleTime.h"
#include "../utils/GuardDataController.h"

namespace onh {

	typedef struct {
		/// Cycle time controller Process updater
		GuardDataController<CycleTimeData> cUpdater;
		/// Cycle time controller Process updater
		GuardDataController<CycleTimeData> cAlarming;
		/// Cycle time controller Logger
		GuardDataController<CycleTimeData> cLogger;
		/// Cycle time controller Logger writer
		GuardDataController<CycleTimeData> cLoggerWriter;
		/// Cycle time controller Script system
		GuardDataController<CycleTimeData> cScript;
		/// Cycle time controller Driver polling
		GuardDataController<CycleTimeData> cDriverPolling;
	} ThreadCycleControllers;

}

#endif /* SRC_ONH_THREAD_THREADCYCLECONTROLLERS_H_ */
