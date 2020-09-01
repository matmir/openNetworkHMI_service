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

#ifndef MUTEXTESTS_H_
#define MUTEXTESTS_H_

#include <gtest/gtest.h>

#include "MutexTestsFixtures.h"

/**
 * Check container locking
 */
TEST_F(mutexTest, ContainerTest1) {

	ASSERT_TRUE(mutexContainer->tryLock());
	ASSERT_FALSE(mutexContainer->tryLock());

	mutexContainer->unlock();

	ASSERT_TRUE(mutexContainer->tryLock());
}

/**
 * Check access locking
 */
TEST_F(mutexTest, AccessTest1) {

	// Mutex access object
	onh::MutexAccess ma(mutexContainer->getAccess());

	ASSERT_TRUE(ma.tryLock());
	ASSERT_FALSE(ma.tryLock());

	ma.unlock();

	ASSERT_TRUE(ma.tryLock());
}

/**
 * Check container/access locking
 */
TEST_F(mutexTest, CATest1) {

	// Mutex access object
	onh::MutexAccess ma(mutexContainer->getAccess());

	ASSERT_TRUE(mutexContainer->tryLock());
	ASSERT_FALSE(ma.tryLock());

	mutexContainer->unlock();

	ASSERT_TRUE(ma.tryLock());
	ASSERT_FALSE(mutexContainer->tryLock());
}

#endif /* MUTEXTESTS_H_ */
