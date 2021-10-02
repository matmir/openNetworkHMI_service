# Cmake build for test server (SHM driver)

cmake_minimum_required(VERSION 3.13.0)

project(onh_test_server1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

find_library(RT_LIB_EX NAMES rt)
if (NOT RT_LIB_EX)
	message(FATAL_ERROR "RT library not found")
endif()

find_library(ONHSHMCPP_EX NAMES onhSHMcpp)
if (NOT ONHSHMCPP_EX)
	message(FATAL_ERROR "onhSHMcpp library not found")
endif()

# Compiler options
add_compile_options(-Wall)

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "Setting build type to 'Release'")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Default build type: Release" FORCE)
endif()

add_executable(${PROJECT_NAME} "")
# source files
include(${PROJECT_SOURCE_DIR}/sourcelist.cmake)

target_link_libraries(${PROJECT_NAME} Threads::Threads onhSHMcpp rt)
