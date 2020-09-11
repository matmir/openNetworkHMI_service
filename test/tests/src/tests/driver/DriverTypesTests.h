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

#ifndef TEST_TESTS_SRC_TESTS_DRIVER_DRIVERTYPESTESTS_H_
#define TEST_TESTS_SRC_TESTS_DRIVER_DRIVERTYPESTESTS_H_

#include <gtest/gtest.h>
#include <driver/DriverRegisterTypes.h>

/**
 * Check data size
 */
TEST(DriverTypes, Type1) {

	ASSERT_EQ(1, sizeof(BYTE));
	ASSERT_EQ(2, sizeof(WORD));
	ASSERT_EQ(4, sizeof(DWORD));
	ASSERT_EQ(4, sizeof(int));
	ASSERT_EQ(4, sizeof(float));
}

#endif /* TEST_TESTS_SRC_TESTS_DRIVER_DRIVERTYPESTESTS_H_ */
