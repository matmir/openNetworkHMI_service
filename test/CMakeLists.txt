# Cmake build for openNetworkHMI tests

cmake_minimum_required(VERSION 3.13.0)

# Test server for SHM driver
add_subdirectory(test_server1)

# Test server for Modbus driver
add_subdirectory(test_server2)

# Main tests
add_subdirectory(tests)