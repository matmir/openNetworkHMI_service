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

#ifndef SRC_DRIVER_SHMSERVER_SHMEXCEPTION_H
#define SRC_DRIVER_SHMSERVER_SHMEXCEPTION_H

#include <exception>
#include <string>

namespace onh {

    /**
     * Base exception class
     */
    class ShmException: public std::exception {

        public:

    		ShmException();
            virtual ~ShmException() noexcept override;

            /**
             * Exception constructor with message
             *
             * @param exceptionMSG Exception additional info
             */
            ShmException(const std::string& exceptionMSG);

            /**
             * Exception constructor with message and function name
             *
             * @param exceptionMSG Exception additional info
             * @param funcName Function from which exception was thrown
             */
            ShmException(const std::string& exceptionMSG, const std::string& funcName);

            /**
             * Get exception message
             *
             * @return Exception message
             */
            virtual const char* what() const noexcept override;

        private:
            /// String with the error message
            std::string errorMessage;

            /// Function from which exception was thrown
            std::string functionName;

            /// Full error message
            std::string allMessage;
    };

}

#endif // SRC_DRIVER_SHMSERVER_SHMEXCEPTION_H
