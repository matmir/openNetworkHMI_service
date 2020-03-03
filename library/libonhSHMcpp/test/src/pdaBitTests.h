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

#ifndef PDABITTESTS_H_
#define PDABITTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"

using namespace onh;

/**
 * Check single input bit
 */
TEST_F(pdaClearTest, TestInputBit1) {

	// 00000100
	pda->setBit(processDataAddress{PDA_INPUT, 1, 2});

	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 1, 2}));
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_INPUT, 1, 0}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(4, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if input bits does not change other bits
 */
TEST_F(pdaClearTest, TestInputBit2) {

	// 00001000
	pda->setBit(processDataAddress{PDA_INPUT, 5, 3});
	// 10001000
	pda->setBit(processDataAddress{PDA_INPUT, 5, 7});
	// 11001000
	pda->setBit(processDataAddress{PDA_INPUT, 5, 6});

	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 5, 3}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 5, 7}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 5, 6}));
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_INPUT, 5, 1}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 5) {
			ASSERT_EQ(200, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single output bit
 */
TEST_F(pdaClearTest, TestOutputBit1) {

	// 00100000
	pda->setBit(processDataAddress{PDA_OUTPUT, 100, 5});

	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_OUTPUT, 100, 5}));
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_OUTPUT, 100, 7}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 100) {
			ASSERT_EQ(32, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if output bits does not change other bits
 */
TEST_F(pdaClearTest, TestOutputBit2) {

	// 00100000
	pda->setBit(processDataAddress{PDA_OUTPUT, 508, 5});
	// 10100000
	pda->setBit(processDataAddress{PDA_OUTPUT, 508, 7});
	// 11100000
	pda->setBit(processDataAddress{PDA_OUTPUT, 508, 6});

	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_OUTPUT, 508, 5}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_OUTPUT, 508, 7}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_OUTPUT, 508, 6}));
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_OUTPUT, 508, 3}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 508) {
			ASSERT_EQ(224, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single memory bit
 */
TEST_F(pdaClearTest, TestMemoryBit1) {

	// 00000001
	pda->setBit(processDataAddress{PDA_MEMORY, 1500, 0});

	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 1500, 0}));
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_MEMORY, 1500, 1}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1500) {
			ASSERT_EQ(1, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check if memory bits does not change other bits
 */
TEST_F(pdaClearTest, TestMemoryBit2) {

	// 00100000
	pda->setBit(processDataAddress{PDA_MEMORY, 3784, 5});
	// 10100000
	pda->setBit(processDataAddress{PDA_MEMORY, 3784, 7});
	// 11100000
	pda->setBit(processDataAddress{PDA_MEMORY, 3784, 6});

	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 3784, 5}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 3784, 7}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 3784, 6}));
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_MEMORY, 3784, 3}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 3784) {
			ASSERT_EQ(224, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWriteBit1) {

	// 00000100
	pda->writeBit(processDataAddress{PDA_INPUT, 1, 2}, true);

	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 1, 2}));
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_INPUT, 1, 0}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(4, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWriteBit2) {

	// 00000100
	pda->setBit(processDataAddress{PDA_INPUT, 1, 2});

	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 1, 2}));
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_INPUT, 1, 0}));

	pda->writeBit(processDataAddress{PDA_INPUT, 1, 2}, false);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check writing multiple bits in multiple areas
 */
TEST_F(pdaClearTest, TestBit1) {

	// 00100000
	pda->setBit(processDataAddress{PDA_INPUT, 1150, 5});
	// 00000010
	pda->setBit(processDataAddress{PDA_MEMORY, 4850, 1});
	// 10000000
	pda->setBit(processDataAddress{PDA_OUTPUT, 4850, 7});
	// 00001000
	pda->setBit(processDataAddress{PDA_OUTPUT, 377, 3});

	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 1150, 5}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 4850, 1}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_OUTPUT, 4850, 7}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_OUTPUT, 377, 3}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i==377) {
			ASSERT_EQ(8, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else if (i==4850){
			ASSERT_EQ(128, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		if (i==1150) {
			ASSERT_EQ(32, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		if (i==4850) {
			ASSERT_EQ(2, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}
	}
}

/**
 * Check exception on set bit (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionSetBit1) {

	try {

		pda->setBit(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+10, 0});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::setBit: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on set bit (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionSetBit2) {

	try {

		pda->setBit(processDataAddress{PDA_INPUT, 9000, 70});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on set bit (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionSetBit3) {

	try {

		pda->setBit(processDataAddress{(processDataArea)5, 150, 2});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on get bit (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionGetBit1) {

	try {

		pda->getBit(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+10, 0});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::getBit: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on get bit (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionGetBit2) {

	try {

		pda->getBit(processDataAddress{PDA_INPUT, 9000, 70});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on get bit (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionGetBit3) {

	try {

		pda->getBit(processDataAddress{(processDataArea)5, 150, 2});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check single reset input bit
 */
TEST_F(pdaClearTest, TestResetInputBit1) {

	// 10110010
	pda->writeByte(processDataAddress{PDA_INPUT, 7, 0}, 178);
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 7, 4}));

	// 10100010
	pda->resetBit(processDataAddress{PDA_INPUT, 7, 4});
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_INPUT, 7, 4}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(162, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if reset input bits does not change other bits
 */
TEST_F(pdaClearTest, TestResetInputBit2) {

	// 10110010
	pda->writeByte(processDataAddress{PDA_INPUT, 7, 0}, 178);
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 7, 4}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 7, 5}));

	// 10100010
	pda->resetBit(processDataAddress{PDA_INPUT, 7, 4});
	// 10000010
	pda->resetBit(processDataAddress{PDA_INPUT, 7, 5});
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_INPUT, 7, 4}));
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_INPUT, 7, 5}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(130, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single reset output bit
 */
TEST_F(pdaClearTest, TestResetOutputBit1) {

	// 10110010
	pda->writeByte(processDataAddress{PDA_OUTPUT, 7, 0}, 178);
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_OUTPUT, 7, 4}));

	// 10100010
	pda->resetBit(processDataAddress{PDA_OUTPUT, 7, 4});
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_OUTPUT, 7, 4}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(162, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if reset output bits does not change other bits
 */
TEST_F(pdaClearTest, TestResetOutputBit2) {

	// 10110010
	pda->writeByte(processDataAddress{PDA_OUTPUT, 7, 0}, 178);
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_OUTPUT, 7, 4}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_OUTPUT, 7, 5}));

	// 10100010
	pda->resetBit(processDataAddress{PDA_OUTPUT, 7, 4});
	// 10000010
	pda->resetBit(processDataAddress{PDA_OUTPUT, 7, 5});
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_OUTPUT, 7, 4}));
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_OUTPUT, 7, 5}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(130, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single reset memory bit
 */
TEST_F(pdaClearTest, TestResetMemoryBit1) {

	// 10110010
	pda->writeByte(processDataAddress{PDA_MEMORY, 7, 0}, 178);
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 7, 4}));

	// 10100010
	pda->resetBit(processDataAddress{PDA_MEMORY, 7, 4});
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_MEMORY, 7, 4}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(162, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check if reset memory bits does not change other bits
 */
TEST_F(pdaClearTest, TestResetMemoryBit2) {

	// 10110010
	pda->writeByte(processDataAddress{PDA_MEMORY, 7, 0}, 178);
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 7, 4}));
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 7, 5}));

	// 10100010
	pda->resetBit(processDataAddress{PDA_MEMORY, 7, 4});
	// 10000010
	pda->resetBit(processDataAddress{PDA_MEMORY, 7, 5});
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_MEMORY, 7, 4}));
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_MEMORY, 7, 5}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(130, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check reset multiple bits in multiple areas
 */
TEST_F(pdaClearTest, TestResetBit1) {

	// 10110010
	pda->writeByte(processDataAddress{PDA_MEMORY, 7, 0}, 178);
	// 00000100
	pda->writeByte(processDataAddress{PDA_INPUT, 230, 0}, 4);
	// 00000101
	pda->writeByte(processDataAddress{PDA_OUTPUT, 231, 0}, 5);

	// 10110000
	pda->resetBit(processDataAddress{PDA_MEMORY, 7, 1});
	// 00000000
	pda->resetBit(processDataAddress{PDA_INPUT, 230, 2});
	// 00000100
	pda->resetBit(processDataAddress{PDA_OUTPUT, 231, 0});

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i==7) {
			ASSERT_EQ(176, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}

		if (i==231) {
			ASSERT_EQ(4, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

/**
 * Check exception on reset bit (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionResetBit1) {

	try {

		pda->resetBit(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+100, 0});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::resetBit: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on reset bit (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionResetBit2) {

	try {

		pda->resetBit(processDataAddress{PDA_INPUT, 9000, 70});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on reset bit (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionResetBit3) {

	try {

		pda->resetBit(processDataAddress{(processDataArea)5, 150, 2});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check invert input bit
 */
TEST_F(pdaClearTest, TestInvertInputBit1) {

	// 10110010
	pda->writeByte(processDataAddress{PDA_INPUT, 7, 0}, 178);
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 7, 4}));

	// 10100010
	pda->invertBit(processDataAddress{PDA_INPUT, 7, 4});
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_INPUT, 7, 4}));

	// 10110010
	pda->invertBit(processDataAddress{PDA_INPUT, 7, 4});
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_INPUT, 7, 4}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(178, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check invert output bit
 */
TEST_F(pdaClearTest, TestInvertOutputBit1) {

	// 10110010
	pda->writeByte(processDataAddress{PDA_OUTPUT, 7, 0}, 178);
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_OUTPUT, 7, 4}));

	// 10100010
	pda->invertBit(processDataAddress{PDA_OUTPUT, 7, 4});
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_OUTPUT, 7, 4}));

	// 10110010
	pda->invertBit(processDataAddress{PDA_OUTPUT, 7, 4});
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_OUTPUT, 7, 4}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(178, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check invert memory bit
 */
TEST_F(pdaClearTest, TestInvertMemoryBit1) {

	// 10110010
	pda->writeByte(processDataAddress{PDA_MEMORY, 7, 0}, 178);
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 7, 4}));

	// 10100010
	pda->invertBit(processDataAddress{PDA_MEMORY, 7, 4});
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_MEMORY, 7, 4}));

	// 10110010
	pda->invertBit(processDataAddress{PDA_MEMORY, 7, 4});
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 7, 4}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(178, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check exception on invert bit (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionInvertBit1) {

	try {

		pda->invertBit(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+10, 0});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::invertBit: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on invert bit (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionInvertBit2) {

	try {

		pda->invertBit(processDataAddress{PDA_INPUT, 9000, 70});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on invert bit (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionInvertBit3) {

	try {

		pda->invertBit(processDataAddress{(processDataArea)5, 150, 2});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check set input bits
 */
TEST_F(pdaClearTest, TestSetInputBits1) {

	// Prepare addresses to set
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_INPUT, 1, 0});
	addr.push_back(processDataAddress{PDA_INPUT, 1, 2});
	addr.push_back(processDataAddress{PDA_INPUT, 1, 3});

	// 00001101
	pda->setBits(addr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check set output bits
 */
TEST_F(pdaClearTest, TestSetOutputBits1) {

	// Prepare addresses to set
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_OUTPUT, 1, 0});
	addr.push_back(processDataAddress{PDA_OUTPUT, 1, 2});
	addr.push_back(processDataAddress{PDA_OUTPUT, 1, 3});

	// 00001101
	pda->setBits(addr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check set memory bits
 */
TEST_F(pdaClearTest, TestSetMemoryBits1) {

	// Prepare addresses to set
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_MEMORY, 1, 0});
	addr.push_back(processDataAddress{PDA_MEMORY, 1, 2});
	addr.push_back(processDataAddress{PDA_MEMORY, 1, 3});

	// 00001101
	pda->setBits(addr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check set bits
 */
TEST_F(pdaClearTest, TestSetBits1) {

	// Prepare addresses to set
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_MEMORY, 1, 0});
	addr.push_back(processDataAddress{PDA_MEMORY, 1, 2});
	addr.push_back(processDataAddress{PDA_INPUT, 100, 5});
	addr.push_back(processDataAddress{PDA_OUTPUT, 4800, 7});

	pda->setBits(addr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(5, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}

		if (i == 100) {
			ASSERT_EQ(32, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		if (i == 4800) {
			ASSERT_EQ(128, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}
	}
}

/**
 * Check exception on set bits (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionSetBits1) {

	// Prepare addresses to set
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_MEMORY, 1, 0});
	addr.push_back(processDataAddress{PDA_MEMORY, PROCESS_DT_SIZE+10, 2});
	addr.push_back(processDataAddress{PDA_INPUT, 100, 5});
	addr.push_back(processDataAddress{PDA_OUTPUT, 4800, 7});

	try {

		pda->setBits(addr);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::setBit: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on set bits (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionSetBits2) {

	// Prepare addresses to set
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_MEMORY, 1, 0});
	addr.push_back(processDataAddress{PDA_MEMORY, 8, 2});
	addr.push_back(processDataAddress{PDA_INPUT, 100, 93});
	addr.push_back(processDataAddress{PDA_OUTPUT, 4800, 7});

	try {

		pda->setBits(addr);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on set bits (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionSetBits3) {

	// Prepare addresses to set
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_MEMORY, 1, 0});
	addr.push_back(processDataAddress{(processDataArea)5, 8, 2});
	addr.push_back(processDataAddress{PDA_INPUT, 100, 93});
	addr.push_back(processDataAddress{PDA_OUTPUT, 4800, 7});

	try {

		pda->setBits(addr);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(),  "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check get bits
 */
TEST_F(pdaClearTest, TestGetBits1) {

	std::vector<bool> ret;

	pda->writeByte(processDataAddress{PDA_INPUT, 1, 0}, 13);
	pda->writeByte(processDataAddress{PDA_OUTPUT, 10, 0}, 197);
	pda->writeByte(processDataAddress{PDA_MEMORY, 78, 0}, 25);

	// Prepare addresses to get
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_INPUT, 1, 0});
	addr.push_back(processDataAddress{PDA_INPUT, 1, 2});
	addr.push_back(processDataAddress{PDA_INPUT, 1, 3});
	addr.push_back(processDataAddress{PDA_OUTPUT, 10, 6});
	addr.push_back(processDataAddress{PDA_OUTPUT, 10, 7});
	addr.push_back(processDataAddress{PDA_MEMORY, 78, 4});
	addr.push_back(processDataAddress{PDA_MEMORY, 78, 5});

	ret = pda->getBits(addr);

	ASSERT_TRUE(ret[0]);
	ASSERT_TRUE(ret[1]);
	ASSERT_TRUE(ret[2]);
	ASSERT_TRUE(ret[3]);
	ASSERT_TRUE(ret[5]);
	ASSERT_FALSE(ret[6]);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		if (i == 10) {
			ASSERT_EQ(197, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		if (i == 78) {
			ASSERT_EQ(25, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}
	}
}

/**
 * Check exception on get bits (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionGetBits1) {

	// Prepare addresses to set
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_MEMORY, 1, 0});
	addr.push_back(processDataAddress{PDA_MEMORY, PROCESS_DT_SIZE+100, 2});
	addr.push_back(processDataAddress{PDA_INPUT, 100, 5});
	addr.push_back(processDataAddress{PDA_OUTPUT, 4800, 7});

	try {

		pda->getBits(addr);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::getBit: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on get bits (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionGetBits2) {

	// Prepare addresses to set
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_MEMORY, 1, 0});
	addr.push_back(processDataAddress{PDA_MEMORY, 8, 2});
	addr.push_back(processDataAddress{PDA_INPUT, 100, 93});
	addr.push_back(processDataAddress{PDA_OUTPUT, 4800, 7});

	try {

		pda->getBits(addr);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on get bits (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionGetBits3) {

	// Prepare addresses to set
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_MEMORY, 1, 0});
	addr.push_back(processDataAddress{(processDataArea)5, 8, 2});
	addr.push_back(processDataAddress{PDA_INPUT, 100, 93});
	addr.push_back(processDataAddress{PDA_OUTPUT, 4800, 7});

	try {

		pda->getBits(addr);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(),  "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

#endif /* PDABITTESTS_H_ */
