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

#ifndef TEST_SRC_TESTS_DB_OBJS_DRIVERCONNECTIONTESTS_H_
#define TEST_SRC_TESTS_DB_OBJS_DRIVERCONNECTIONTESTS_H_

#include <gtest/gtest.h>
#include <db/objs/DriverConnection.h>

/**
 * Check connection creation
 */
TEST(DriverConnectionTests, Create1) {

	onh::DriverConnection conn1;
	conn1.setId(1);
	conn1.setName("testConn");
	conn1.setType(onh::DriverType::DT_SHM);
	conn1.setShmCfg("shm1");

	ASSERT_EQ((unsigned int)1, conn1.getId());
	ASSERT_STREQ("testConn", conn1.getName().c_str());
	ASSERT_EQ(onh::DriverType::DT_SHM, conn1.getType());
	ASSERT_STREQ("shm1", conn1.getShmCfg().c_str());
	ASSERT_FALSE(conn1.isEnabled());
}

/**
 * Check connection creation set enable
 */
TEST(DriverConnectionTests, CreateSetEnable) {

	onh::DriverConnection conn1;
	conn1.setId(1);
	conn1.setName("testConn");
	conn1.setType(onh::DriverType::DT_SHM);
	conn1.setShmCfg("shm1");
	conn1.setEnable(true);

	ASSERT_EQ((unsigned int)1, conn1.getId());
	ASSERT_STREQ("testConn", conn1.getName().c_str());
	ASSERT_EQ(onh::DriverType::DT_SHM, conn1.getType());
	ASSERT_STREQ("shm1", conn1.getShmCfg().c_str());
	ASSERT_TRUE(conn1.isEnabled());
}

/**
 * Check connection creation Exception 1
 */
TEST(DriverConnectionTests, CreateException1) {

	onh::DriverConnection conn1;
	conn1.setId(1);
	conn1.setName("testConn");
	conn1.setType(onh::DriverType::DT_SHM);
	conn1.setShmCfg("shm1");

	try {

		conn1.getModbusCfg();

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "DriverConnection::getModbusCfg: Driver connection wrong driver type");

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check connection creation Exception 2
 */
TEST(DriverConnectionTests, CreateException2) {

	onh::DriverConnection conn1;
	conn1.setId(1);
	conn1.setName("testConn");
	conn1.setType(onh::DriverType::DT_SHM);
	conn1.setShmCfg("shm1");

	modbusM::ModbusCfg mb;

	try {

		conn1.setModbusCfg(mb);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "DriverConnection::setModbusCfg: Driver connection wrong driver type");

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check connection creation
 */
TEST(DriverConnectionTests, Create2) {

	modbusM::ModbusCfg mb;
	mb.mode = modbusM::MM_TCP;
	mb.slaveID = 56;
	mb.registerCount = 20;
	mb.polling = 200;
	mb.TCP_addr = "192.168.5.5";
	mb.TCP_port = 504;

	onh::DriverConnection conn1;
	conn1.setId(1);
	conn1.setName("testConn");
	conn1.setType(onh::DriverType::DT_Modbus);
	conn1.setModbusCfg(mb);

	ASSERT_EQ((unsigned int)1, conn1.getId());
	ASSERT_STREQ("testConn", conn1.getName().c_str());
	ASSERT_EQ(onh::DriverType::DT_Modbus, conn1.getType());
	ASSERT_EQ(modbusM::MM_TCP, conn1.getModbusCfg().mode);
	ASSERT_EQ(56, conn1.getModbusCfg().slaveID);
	ASSERT_EQ(20, conn1.getModbusCfg().registerCount);
	ASSERT_EQ(200, conn1.getModbusCfg().polling);
	ASSERT_STREQ("192.168.5.5", conn1.getModbusCfg().TCP_addr.c_str());
	ASSERT_EQ(504, conn1.getModbusCfg().TCP_port);
	ASSERT_FALSE(conn1.isEnabled());
}

/**
 * Check connection creation Exception 3
 */
TEST(DriverConnectionTests, CreateException3) {

	modbusM::ModbusCfg mb;
	mb.mode = modbusM::MM_TCP;
	mb.slaveID = 56;
	mb.registerCount = 20;
	mb.polling = 200;
	mb.TCP_addr = "192.168.5.5";
	mb.TCP_port = 504;

	onh::DriverConnection conn1;
	conn1.setId(1);
	conn1.setName("testConn");
	conn1.setType(onh::DriverType::DT_Modbus);
	conn1.setModbusCfg(mb);

	try {

		conn1.getShmCfg();

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "DriverConnection::checkShmCfg: Driver connection wrong driver type");

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check connection creation Exception 4
 */
TEST(DriverConnectionTests, CreateException4) {

	modbusM::ModbusCfg mb;
	mb.mode = modbusM::MM_TCP;
	mb.slaveID = 56;
	mb.registerCount = 20;
	mb.polling = 200;
	mb.TCP_addr = "192.168.5.5";
	mb.TCP_port = 504;

	onh::DriverConnection conn1;
	conn1.setId(1);
	conn1.setName("testConn");
	conn1.setType(onh::DriverType::DT_Modbus);
	conn1.setModbusCfg(mb);

	try {

		conn1.setShmCfg("test");

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "DriverConnection::checkShmCfg: Driver connection wrong driver type");

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

#endif /* TEST_SRC_TESTS_DB_OBJS_DRIVERCONNECTIONTESTS_H_ */
