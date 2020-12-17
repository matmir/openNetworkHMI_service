# Source files

set(lib_pub_headers
	"include/${PROJECT_NAME}/processData.h"
	"include/${PROJECT_NAME}/processDataAccess.h"
	"include/${PROJECT_NAME}/sCommands.h"
	"include/${PROJECT_NAME}/sMemory.h"
	"include/${PROJECT_NAME}/sMemoryServer.h"
	"include/${PROJECT_NAME}/sMemoryServerProg.h"
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${lib_pub_headers}")

target_sources(${PROJECT_NAME} PRIVATE
    "src/processDataAccess.c"
    "src/sMemoryServer.c"
    "src/sMemoryServerProg.c"
)