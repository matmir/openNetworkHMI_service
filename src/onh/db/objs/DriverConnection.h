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

#ifndef SRC_ONH_DB_OBJS_DRIVERCONNECTION_H_
#define SRC_ONH_DB_OBJS_DRIVERCONNECTION_H_

#include <string>
#include "../../driver/Modbus/modbusmasterCfg.h"

namespace onh {

	/**
	 * Driver types
	 */
    typedef enum {
        DT_SHM = 0,
        DT_Modbus = 1
    } DriverType;

    /**
     * Driver connection class
     */
	class DriverConnection {

		public:

    		/**
    		 * Max allowed connection numbers
    		 */
    		static const int MAX_CONN = 5;

    		/**
    		 * Default constructor
    		 */
			DriverConnection();

			/**
			 * Copy constructor
			 *
			 * @param dc Driver connection object to copy
			 */
			DriverConnection(const DriverConnection& dc);

			virtual ~DriverConnection();

			/**
			 * Assign operator
			 *
			 * @param dc Driver connection object to assign
			 */
			DriverConnection& operator=(const DriverConnection& dc);

			/**
			 * Get Driver connection identifier
			 *
			 * @return Driver connection id
			 */
			unsigned int getId() const;

			/**
			 * Set Driver connection identifier
			 *
			 * @param id Driver connection identifier
			 */
			void setId(unsigned int id);

			/**
			 * Get Driver connection name
			 *
			 * @return Driver connection name
			 */
			std::string getName() const;

			/**
			 * Set Driver connection name
			 *
			 * @param nm Driver connection name
			 */
			void setName(const std::string& nm);

			/**
			 * Get Driver connection type
			 *
			 * @return Driver connection type
			 */
			DriverType getType() const;

			/**
			 * Set Driver connection type
			 *
			 * @param type Driver connection type
			 */
			void setType(const DriverType& type);

			/**
			 * Get Modbus driver configuration
			 *
			 * @return Modbus driver configuration
			 */
			const modbusM::ModbusCfg& getModbusCfg() const;

			/**
			 * Set Modbus driver configuration
			 *
			 * @param cfg Modbus driver configuration
			 */
			void setModbusCfg(const modbusM::ModbusCfg& cfg);

			/**
			 * Get SHM driver configuration
			 *
			 * @return SHM driver configuration
			 */
			const std::string& getShmCfg() const;

			/**
			 * Set SHM driver configuration
			 *
			 * @param cfg SHM driver configuration
			 */
			void setShmCfg(const std::string& cfg);

			/**
			 * Get Driver connection enable flag
			 *
			 * @return Driver connection enable flag
			 */
			bool isEnabled() const;

			/**
			 * Set Driver connection enable flag
			 *
			 * @param enable Driver connection enable flag
			 */
			void setEnable(bool enable);

		private:

			/// Driver connection identifier
			unsigned int dcId;

			/// Driver connection name
			std::string dcName;

			/// Driver connection type
			DriverType dcType;

			/// Modbus configuration
			modbusM::ModbusCfg *modbus;

			/// SHM configuration (segment name)
			std::string shm;

			/// Driver connection enable flag
			bool dcEnable;

			/**
			 * Check Driver connection identifier
			 *
			 * @param id Identifier
			 */
			void checkId(unsigned int id) const;

			/**
			 * Check Driver connection name
			 * @param nm Driver connection name
			 */
			void checkName(const std::string& nm) const;

			/**
			 * Check Driver connection type
			 *
			 * @param type Driver connection type
			 */
			void checkType(const DriverType& type) const;

			/**
			 * Check SHM configuration
			 * @param cfg SHM configuration
			 */
			void checkShmCfg(const std::string& cfg) const;
	};

}

#endif /* SRC_ONH_DB_OBJS_DRIVERCONNECTION_H_ */
