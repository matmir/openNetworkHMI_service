/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2021 Mateusz Mirosławski.
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

#ifndef ONH_DB_CONFIG_H_
#define ONH_DB_CONFIG_H_

#include <string>
#include <vector>
#include "objs/DriverConnection.h"
#include "DB.h"

namespace onh {

/// Forward declaration
class DBManager;

/**
 * Class for read/write application configuration from DB
 */
class Config: public DB {
	public:
		friend class DBManager;

		/**
		 * Copy constructor
		 *
		 * @param cDB Config object to copy
		 */
		Config(const Config &cDB);

		~Config() override;

		/**
		 * Assign operator - inactive
		 */
		Config& operator=(const Config&) = delete;

		/**
		 * Get string value from configuration DB
		 *
		 * @param field Configuration name
		 */
		std::string getStringValue(const std::string& field);

		/**
		 * Get int value from configuration DB
		 *
		 * @param field Configuration name
		 */
		int getIntValue(const std::string& field);

		/**
		 * Get unsigned int value from configuration DB
		 *
		 * @param field Configuration name
		 */
		unsigned int getUIntValue(const std::string& field);

		/**
		 * Set int value in configuration DB
		 *
		 * @param field Configuration name
		 */
		void setValue(const std::string& field, int val);

		/**
		 * Set string value in configuration DB
		 *
		 * @param field Configuration name
		 */
		void setValue(const std::string& field, const std::string& val);

		/**
		 * Get Driver connections
		 *
		 * @param enabled Get only enabled connections
		 *
		 * @return Driver connections
		 */
		std::vector<DriverConnection> getDriverConnections(bool enabled = true);

	private:
		/**
		 * Constructor with connection param (allowed only from DBManager)
		 *
		 * @param connection Connection handle
		 */
		explicit Config(MYSQL *connDB);

		/**
		 * Get SHM driver configuration
		 *
		 * @param id SHM driver identifier
		 * @return SHM driver configuration
		 */
		std::string getShmCfg(unsigned int id);

		/**
		 * Get Modbus driver configuration
		 *
		 * @param id Modbus driver identifier
		 * @return Modbus driver identifier
		 */
		modbusM::ModbusCfg getModbusCfg(unsigned int id);

		/**
		 * Check driver connection limit
		 */
		void checkDriverConnectionLimit();
};

}  // namespace onh

#endif  // ONH_DB_CONFIG_H_
