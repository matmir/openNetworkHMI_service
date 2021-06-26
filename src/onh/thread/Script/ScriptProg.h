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

#ifndef ONH_THREAD_SCRIPT_SCRIPTPROG_H_
#define ONH_THREAD_SCRIPT_SCRIPTPROG_H_

#include "../../driver/ProcessReader.h"
#include "../../driver/ProcessWriter.h"
#include "../../utils/Delay.h"
#include "../ThreadProgram.h"
#include "../../db/ScriptDB.h"

namespace onh {

/**
 * Script system program class
 */
class ScriptProg: public ThreadProgram {
	public:
		/**
		 * Constructor
		 *
		 * @param pr Process reader
		 * @param pw Proces writer
		 * @param sdb Script DB
		 * @param updateInterval Script system update interval (milliseconds)
		 * @param execScript Full path to the main execute script
		 * @param tstEnv Test environment flag
		 * @param gdcTED Thread exit data controller
		 * @param gdcCTD Thread cycle time controller
		 */
		ScriptProg(const ProcessReader& pr,
					const ProcessWriter& pw,
					const ScriptDB& sdb,
					unsigned int updateInterval,
					const std::string& execScript,
					bool tstEnv,
					const GuardDataController<ThreadExitData> &gdcTED,
					const GuardDataController<CycleTimeData> &gdcCTD);

		/**
		 * Copy constructor - inactive
		 */
		ScriptProg(const ScriptProg&) = delete;

		virtual ~ScriptProg();

		/**
		 * Thread program function
		 */
		void operator()() override;

		/**
		 * Assignment operator - inactive
		 */
		ScriptProg& operator=(const ScriptProg&) = delete;

	private:
		/// Handle for process reader object
		std::unique_ptr<ProcessReader> prReader;

		/// Handle for process writer object
		std::unique_ptr<ProcessWriter> prWriter;

		/// Script DB access
		std::unique_ptr<ScriptDB> db;

		/// Full path to the main execute script
		std::string executeScript;

		/// Flag informs that log (redirected script output) directory exist
		bool dirReady;

		/// Test environment flag
		bool testEnv;

		/// Check scripts
		void checkScripts();
};

}  // namespace onh

#endif  // ONH_THREAD_SCRIPT_SCRIPTPROG_H_
