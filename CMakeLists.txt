# Cmake build for openNetworkHMI

cmake_minimum_required(VERSION 3.13.0)

project(openNetworkHMI VERSION 0.9.5)
configure_file(${PROJECT_SOURCE_DIR}/appConfig.h.in ${PROJECT_SOURCE_DIR}/src/appConfig.h)
message(STATUS "Generating ${PROJECT_NAME} version: ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

find_library(RT_LIB_EX NAMES rt)
if (NOT RT_LIB_EX)
	message(FATAL_ERROR "RT library not found")
endif()

# Find Modbus library
find_library(MODBUS_LIB_EX NAMES modbus)
find_path(MODBUS_INCLUDE_DIR NAMES modbus.h
          PATH_SUFFIXES include modbus include/modbus
          PATHS /usr/include/modbus)
if (NOT MODBUS_LIB_EX OR NOT MODBUS_INCLUDE_DIR)
	message(FATAL_ERROR "modbus library not found")
endif()

# Find MariaDB library
find_library(MARIADB_LIB_EX NAMES mariadb)
find_path(MARIADB_INCLUDE_DIR NAMES mysql.h
          PATH_SUFFIXES include mariadb include/mariadb
          PATHS /usr/include/mariadb)
if (NOT MARIADB_LIB_EX OR NOT MARIADB_INCLUDE_DIR)
	message(FATAL_ERROR "mariadb library not found")
endif()

# Compiler options
add_compile_options(-Wall)

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "Setting build type to 'Release'")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Default build type: Release" FORCE)
endif()

# Option for test compilation
option(WithTest "Build with test" OFF)

add_executable(${PROJECT_NAME} "")
# source files
include(${PROJECT_SOURCE_DIR}/sourcelist.cmake)

target_link_libraries(${PROJECT_NAME} Threads::Threads rt modbus mariadb)
target_include_directories(${PROJECT_NAME} PRIVATE
	${MARIADB_INCLUDE_DIR}
	${MODBUS_INCLUDE_DIR}
)

# test compilation
if (WithTest)
	message(STATUS "Building tests Enabled")
	add_subdirectory(test)
else()
	message(STATUS "Building tests Disabled")
endif()
