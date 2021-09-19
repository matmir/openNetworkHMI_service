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

#ifndef ONH_THREAD_SCRIPT_SCRIPTRUNNER_H_
#define ONH_THREAD_SCRIPT_SCRIPTRUNNER_H_

#include <string>
#include <atomic>
#include <thread>

namespace onh {

/**
 * Script runner class
 */
class ScriptRunner {
	public:
		/**
		 * Constructor
		 *
		 * @param scriptPath Path to the script to be executed
		 * @param scriptOutputLogName Name of the file containing output from the script
		 */
		ScriptRunner(const std::string &scriptPath,
				const std::string &scriptOutputLogName);

		/**
		 * Copy constructor - inactive
		 */
		ScriptRunner(const ScriptRunner&) = delete;

		/**
		 * Destructor
		 */
		virtual ~ScriptRunner();

		/**
		 * Assignment operator - inactive
		 */
		ScriptRunner& operator=(const ScriptRunner&) = delete;

		/**
		 * Get runner finish flag
		 */
		bool finished() const;

	private:
		/// Path to the script to be executed
		const std::string script;
		/// Name of the file containing output from the script
		const std::string scriptLog;

		/// Script finish flag
		std::atomic<bool> scriptFinished;

		/// Script thread
		std::thread th;
};

}  // namespace onh

#endif  // ONH_THREAD_SCRIPT_SCRIPTRUNNER_H_
