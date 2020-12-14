# Cmake build for libonhSHMcpp

cmake_minimum_required(VERSION 3.13.0)

project(onhSHMcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler options
add_compile_options(-Wall -Wno-int-in-bool-context)

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "Setting build type to 'Release'.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Default build type: Release" FORCE)
endif()

# Option for test compilation
option(WithTest "Build with test" OFF)

include_directories(include)

add_library(${PROJECT_NAME} STATIC "")

# source files
include(${PROJECT_SOURCE_DIR}/sourcelist.cmake)

# test compilation
if (WithTest)
	message(STATUS "Building tests Enabled.")
	add_subdirectory(test)
else()
	message(STATUS "Building tests Disabled.")
endif()

install(TARGETS ${PROJECT_NAME}
	ARCHIVE DESTINATION "/usr/local/lib"
	PUBLIC_HEADER DESTINATION "/usr/local/include/${PROJECT_NAME}/"
)