/**
 * Copyright (c) 2021 Mateusz Mirosławski
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

#ifndef ONH_DRIVER_SHM_SCOMMANDS_H_
#define ONH_DRIVER_SHM_SCOMMANDS_H_

#define DRV_PROC_IN 500
#define DRV_PROC_OUT 501
#define DRV_PROC_MEM 502

/// Close server
#define DRV_CMD_EXIT 0

/// Unknown command
#define DRV_CMD_UNKNOWN -1

/// Command executed properly
#define DRV_CMD_OK 1

/// Command not executed - error
#define DRV_CMD_NOK 2

/// Ping command
#define DRV_CMD_PING 100
/// Pong command
#define DRV_CMD_PONG 101

/// Test command
#define DRV_CMD_TEST 5000

//------------------------------------------
//        MODIFY PROCESS DATA
//------------------------------------------

/// Set bit
#define DRV_SET_BIT 110

/// Reset bit
#define DRV_RESET_BIT 111

/// Invert bit
#define DRV_INVERT_BIT 112

/// Set bits
#define DRV_SET_BITS 120

/// Write byte
#define DRV_WRITE_BYTE 130

/// Write word
#define DRV_WRITE_WORD 131

/// Write double word
#define DRV_WRITE_DWORD 132

/// Write integer
#define DRV_WRITE_INT 133

/// Write real
#define DRV_WRITE_REAL 134

#endif  // ONH_DRIVER_SHM_SCOMMANDS_H_
