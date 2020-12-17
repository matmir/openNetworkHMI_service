# Source files

# Test files
target_sources(${PROJECT_NAME} PRIVATE
    "src/Server_C_test.cpp"
    "src/shmServerTests.h"
    "src/pdaBitTests.h"
    "src/pdaByteTests.h"
    "src/pdaDWordTests.h"
    "src/pdaIntTests.h"
    "src/pdaRealTests.h"
    "src/pdaTestGlobalData.h"
    "src/pdaWordTests.h"
    "src/fixtures/pdaClearTest.h"
    "src/fixtures/shmServerClearTest.h"
)

# Program files to test
target_sources(${PROJECT_NAME} PRIVATE
    "../src/processDataAccess.c"
    "../src/sMemoryServer.c"
    "../src/sMemoryServerProg.c"
)