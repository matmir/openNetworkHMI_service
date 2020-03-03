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
#include <signal.h>
#include <string.h>

#include "Application.h"

using namespace std;

bool exitSignal;

// Exit signal function
void term(int signum) {

	exitSignal = true;
}

int main() {

	exitSignal = false;

	cout << "C++ SHM test server program!\n" << endl;
	// Remove init file
	system("rm -f shmInited");

	// --------------------- PROGRAM TERMINATION --------------------------
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = term;
	sigaction(SIGTERM, &action, NULL);

	// Run app
	Application app("onh_SHM_segment_test1", &exitSignal);
	app.run();

	cout << "Test server program closed!" << endl;
}