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

#ifndef PROCESSREADWRITE_H
#define PROCESSREADWRITE_H

#include "Driver.h"
#include "../db/objs/Tag.h"
#include "../utils/MutexAccess.h"

namespace onh {

    /**
     * Process data access base class
     */
    class ProcessReadWrite {

        public:

            ProcessReadWrite();

            virtual ~ProcessReadWrite();

        protected:

            /**
             * Triggers tag type error
             *
             * @param tagName Tag name
             * @param fName Function from which exception was throwed
             */
            void triggerTagTypeError(const std::string& tagName, const std::string& fName) const;

            /**
             * Triggers tag area error
             *
             * @param tagName Tag name
             * @param fName Function from which exception was throwed
             */
            void triggerTagAreaError(const std::string& tagName, const std::string& fName) const;

            /**
             * Triggers error
             *
             * @param msg Exception message
             * @param tagName Tag name
             * @param fName Function from which exception was throwed
             */
            void triggerError(const std::string& msg, const std::string& tagName, const std::string& fName) const;
    };

}

#endif // PROCESSREADWRITE_H
