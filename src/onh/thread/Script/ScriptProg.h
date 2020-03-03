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

#ifndef SCRIPTPROG_H
#define SCRIPTPROG_H

#include "ScriptThreadData.h"
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
             * @param thData Script system thread data structure
             */
            ScriptProg(const ScriptThreadData &thData);

            virtual ~ScriptProg();

            /**
             * Run Script system
             */
            void run();

        private:

            /// Handle for process reader object
            ProcessReader* prReader;

            /// Handle for process writer object
            ProcessWriter* prWriter;

            /// Timer delay object
            Delay* itsDelay;

            /// Script DB access
            ScriptDB *db;

            /// Full path to the main execute script
            std::string executeScript;

            /// Flag informs that log (redirected script output) directory exist
            bool dirReady;

            /// Test environment flag
            bool testEnv;

            /// Check scripts
            void checkScripts();
    };

}

#endif // SCRIPTPROG_H