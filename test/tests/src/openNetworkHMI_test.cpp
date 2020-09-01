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

#include <iostream>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <gtest/gtest.h>

#include "tests/testGlobalData.h"

#include "tests/utils/StringUtilsTests.h"
#include "tests/utils/LoggerTests.h"
#include "tests/utils/MutexTests.h"
#include "tests/utils/CycleTimeTests.h"
#include "tests/utils/DelayTests.h"
#include "tests/utils/GuardDataControllerTests.h"

#include "tests/db/objs/TagTests.h"
#include "tests/db/objs/TagLoggerItemTests.h"
#include "tests/db/objs/AlarmDefinitionItemTests.h"
#include "tests/db/objs/AlarmDefinitionItemTestsBit.h"
#include "tests/db/objs/AlarmDefinitionItemTestsByte.h"
#include "tests/db/objs/AlarmDefinitionItemTestsWord.h"
#include "tests/db/objs/AlarmDefinitionItemTestsDWord.h"
#include "tests/db/objs/AlarmDefinitionItemTestsInt.h"
#include "tests/db/objs/AlarmDefinitionItemTestsReal.h"
#include "tests/db/objs/ScriptItemTests.h"
#include "tests/db/objs/DriverConnectionTests.h"

#include "tests/driver/SHM/ShmDriverBitTests.h"
#include "tests/driver/SHM/ShmDriverByteTests.h"
#include "tests/driver/SHM/ShmDriverWordTests.h"
#include "tests/driver/SHM/ShmDriverDWordTests.h"
#include "tests/driver/SHM/ShmDriverIntTests.h"
#include "tests/driver/SHM/ShmDriverRealTests.h"

#include "tests/driver/ProcessReaderTests.h"
#include "tests/driver/ProcessWriterTests.h"
#include "tests/driver/ProcessUpdaterTests.h"
#include <driver/SHM/ShmProcessWriter.h>

using namespace std;

int main(int argc, char **argv) {

	cout << "openNetworkHMI tests" << endl;

	// Run tests
	testing::InitGoogleTest(&argc, argv);
	int tstRes = RUN_ALL_TESTS();

	try {

		// Create SHM driver instance
		onh::ShmDriver sDriver(SHM_SEGMENT_NAME);
		onh::DriverProcessWriter *dWriter = sDriver.getWriter();
		onh::ShmProcessWriter *sWriter = dynamic_cast<onh::ShmProcessWriter*>(dWriter);

		// Close server app
		sWriter->sendServerExitCommand();

		delete sWriter;
	} catch (onh::Exception &e) {
		cout << e.what() << endl;
	}

	// Remove all log files
	system("rm -r -f logs");

	return tstRes;
}
