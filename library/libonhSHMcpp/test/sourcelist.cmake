# Source files

# Test files
target_sources(${PROJECT_NAME} PRIVATE
    "src/Server_CPP_test.cpp"
    "src/shmServerTests.h"
    "src/pdaBitTests.h"
    "src/pdaByteTests.h"
    "src/pdaDWordTests.h"
    "src/pdaIntTests.h"
    "src/pdaRealTests.h"
    "src/pdaTestGlobalData.h"
    "src/pdaWordTests.h"
    "src/PDTagBitTests.h"
    "src/PDTagByteTests.h"
    "src/PDTagDWordTests.h"
    "src/PDTagIntTests.h"
    "src/PDTagRealTests.h"
    "src/PDTagWordTests.h"
    "src/fixtures/pdaClearTest.h"
    "src/fixtures/shmServerClearTest.h"
)

# Program files to test
target_sources(${PROJECT_NAME} PRIVATE
    "../src/MutexAccess.cpp"
    "../src/MutexContainer.cpp"
    "../src/PDTag.cpp"
    "../src/processDataAccess.cpp"
    "../src/ShmException.cpp"
    "../src/ShmServer.cpp"
)