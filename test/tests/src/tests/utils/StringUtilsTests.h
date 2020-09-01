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

#ifndef STRINGUTILSTESTS_H_
#define STRINGUTILSTESTS_H_

#include <gtest/gtest.h>
#include <utils/StringUtils.h>

/**
 * Check explode
 */
TEST(StringUtilsTests, Explode1) {

	std::string s = "Test^String";
	std::vector<std::string> ex = onh::StringUtils::explode(s, '^');

	ASSERT_EQ((unsigned int)2, ex.size());
	ASSERT_STREQ("Test", ex[0].c_str());
	ASSERT_STREQ("String", ex[1].c_str());
}

/**
 * Check explode without separator
 */
TEST(StringUtilsTests, Explode2) {

	std::string s = "Test^String";
	std::vector<std::string> ex = onh::StringUtils::explode(s, '*');

	ASSERT_EQ((unsigned int)1, ex.size());
	ASSERT_STREQ(s.c_str(), ex[0].c_str());
}

/**
 * Check explode without string value
 */
TEST(StringUtilsTests, ExplodeException1) {

	std::string s = "";

	try {

		std::vector<std::string> ex = onh::StringUtils::explode(s, '^');

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "StringUtils::explode: No data");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check explode without separator value
 */
TEST(StringUtilsTests, ExplodeException2) {

	std::string s = "Test^String";

	try {

		std::vector<std::string> ex = onh::StringUtils::explode(s, 0);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "StringUtils::explode: No data");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check replace
 */
TEST(StringUtilsTests, Replace1) {

	std::string s = "Test^String";
	std::string srpl = onh::StringUtils::replaceChar(s, '^', ' ');

	ASSERT_STREQ("Test String", srpl.c_str());
}

/**
 * Check replace without string value
 */
TEST(StringUtilsTests, ReplaceException1) {

	std::string s = "";

	try {

		std::string srpl = onh::StringUtils::replaceChar(s, '^', ' ');

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "StringUtils::replaceChar: No data");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check replace without char value
 */
TEST(StringUtilsTests, ReplaceException2) {

	std::string s = "Test^String";

	try {

		std::string srpl = onh::StringUtils::replaceChar(s, 0, ' ');

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "StringUtils::replaceChar: No data");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check replace without char value
 */
TEST(StringUtilsTests, ReplaceException3) {

	std::string s = "Test^String";

	try {

		std::string srpl = onh::StringUtils::replaceChar(s, '^', 0);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "StringUtils::replaceChar: No data");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

#endif /* STRINGUTILSTESTS_H_ */
