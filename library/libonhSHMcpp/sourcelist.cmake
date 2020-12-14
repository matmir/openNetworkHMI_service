# Source files

set(lib_pub_headers
	"include/${PROJECT_NAME}/DriverRegisterTypes.h"
	"include/${PROJECT_NAME}/MutexAccess.h"
	"include/${PROJECT_NAME}/MutexContainer.h"
	"include/${PROJECT_NAME}/PDTag.h"
	"include/${PROJECT_NAME}/processData.h"
	"include/${PROJECT_NAME}/processDataAccess.h"
	"include/${PROJECT_NAME}/ProcessDataTypes.h"
	"include/${PROJECT_NAME}/sCommands.h"
	"include/${PROJECT_NAME}/ShmException.h"
	"include/${PROJECT_NAME}/ShmServer.h"
	"include/${PROJECT_NAME}/sMemory.h"
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${lib_pub_headers}")

target_sources(${PROJECT_NAME} PRIVATE
    "src/MutexAccess.cpp"
    "src/MutexContainer.cpp"
    "src/PDTag.cpp"
    "src/processDataAccess.cpp"
    "src/ShmException.cpp"
    "src/ShmServer.cpp"
)