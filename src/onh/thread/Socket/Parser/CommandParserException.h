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

#ifndef COMMANDPARSEREXCEPTION_H
#define COMMANDPARSEREXCEPTION_H

#include "../../../utils/Exception.h"

namespace onh {

    /**
     * Command parser exception class
     */
    class CommandParserException: public Exception {

        public:

            /// Command exception type
            enum ExceptionType {
                NONE = 0,
                WRONG_DATA,
                WRONG_DATA_COUNT,
                CONVERSION_COMMAND,
                UNKNOWN_COMMAND
            };

            CommandParserException();

            virtual ~CommandParserException();

            /**
             * Exception constructor
             *
             * @param type Exception type
             * @param desc Additional exception information
             * @param fName Function from which exception was throwed
             */
            CommandParserException(ExceptionType type, const std::string& desc = "", const std::string& fName = "");

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

#endif // COMMANDPARSEREXCEPTION_H
