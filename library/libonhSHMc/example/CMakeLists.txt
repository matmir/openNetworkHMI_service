# Cmake build for onhSHM_c_example

cmake_minimum_required(VERSION 3.13.0)

project(onhSHM_c_example)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

find_package(GTest REQUIRED)

find_library(RT_LIB_EX NAMES rt)
if (NOT RT_LIB_EX)
	message(FATAL_ERROR "RT library not found")
endif()

find_library(ONHSHMC_EX NAMES onhSHMc)
if (NOT ONHSHMC_EX)
	message(FATAL_ERROR "onhSHMc library not found")
endif()

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "Setting build type to 'Release'")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Default build type: Release" FORCE)
endif()

# Compiler options
add_compile_options(-Wall)

add_executable(${PROJECT_NAME} "src/server.c")
target_link_libraries(${PROJECT_NAME} gtest Threads::Threads rt onhSHMc)
