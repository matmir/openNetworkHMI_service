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
#include <string.h>

#include "Application.h"

using namespace onh;

int main(int argc, char *argv[]) {

    // Test environment flag
    bool testEnv = false;

    // Check parameters
    if (argc == 2) {
    	// Check test flag
    	if (strcmp(argv[1], "test") == 0) {
    		testEnv = true;
    	}
    }

    // Create application
	Application app(testEnv);

	return app.start();
}
