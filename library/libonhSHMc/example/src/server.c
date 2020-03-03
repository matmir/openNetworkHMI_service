/**
 * Copyright (c) 2020 Mateusz Mirosławski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <errno.h>

#include <onhSHMc/sMemoryServerProg.h>

// Close program
int closeProg = 0;

// Terminate signal function
void term(int signum)
{
    closeProg = 1;
}

// Sleep for millisecond
int msleep(unsigned int tms)
{
    struct timespec ts;
    int ret;

    ts.tv_sec = tms / 1000;
    ts.tv_nsec = (tms % 1000) * 1000000;

    do {
        ret = nanosleep(&ts, &ts);
    } while (ret && errno == EINTR);

    return ret;
}

int main(int argc, char* argv[])
{
    printf("Server program...\n");

    closeProg = 0;

    // Process data
    processData procDT;

    int parseErr = 0;

    // clear all registers
    for (int i=0; i<PROCESS_DT_SIZE; ++i) {
        procDT.in[i] = 0;
        procDT.out[i] = 0;
        procDT.mem[i] = 0;
    }

    // --------------------- PROGRAM TERMINATION --------------------------
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);

    // --------------------- PREPARE SHARED MEMORY ------------------------

	// Server SHM data
	shm_serverData ssdt = {"onh_shm_segment", 0, 0};

    // Initialize shared memory
	parseErr = shm_initMemory(&ssdt);
	if (parseErr != SHM_ERROR_NONE) {
		printf("Prepare Shared Memory error: %d\n", parseErr);
		exit(-1);
	}

    int additionalErr = 0;
    parseErr = 0;
    int copyErr = 0;
    // ------------------------ MAIN LOOP ------------------------
    while(closeProg == 0) {

        // READ INPUT DATA

        // READ COMMAND DATA
        parseErr = parseClientCommand(&ssdt, &closeProg, &procDT, &additionalErr);
        if (parseErr != SERVER_ERROR_NONE) {
        	closeProg = 1;
        }

        // DO CONTROLL PROGRAM

        // WRITE OUTPUT DATA

        // Copy process data to the shared memory
        copyErr = copyProcessData(&ssdt, &procDT, &additionalErr);
        if (copyErr != SERVER_ERROR_NONE) {
			closeProg = 1;
		}

        // Sleep 10ms
        msleep(10);
   }
   // ------------------------------------------------------------

    shm_closeMemory(&ssdt);

    printf("Server program closed!\n");
}
