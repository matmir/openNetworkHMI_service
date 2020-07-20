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

#ifndef SCRIPTEXCEPTION_H
#define SCRIPTEXCEPTION_H

#include "../../utils/Exception.h"

namespace onh {

    /**
     * Script exception class
     */
    class ScriptException: public Exception
    {
        public:

            /// SCript exception type
            typedef enum {
            	NONE = 0,
                WRONG_ID,
                WRONG_NAME,
				WRONG_TAG_TYPE,
				NO_TAG,
                NO_FEEDBACK_RUN_TAG
            } ExceptionType;

            ScriptException();

            virtual ~ScriptException() noexcept;

            /**
             * Exception constructor
             *
             * @param type Exception type
             * @param desc Additional exception information
             * @param fName Function from which exception was thrown
             */
            ScriptException(ExceptionType type, const std::string& desc = "", const std::string& fName = "");

            /**
             * Get exception type
             *
             * @return Exception type
             */
            ExceptionType getType() const;

        private:

            /// Exception type
            ExceptionType exType;
    };

}

#endif // SCRIPTEXCEPTION_H
