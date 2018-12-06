cmake_minimum_required(VERSION 2.6)
project(test_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_C_COMPILER "${COMPILER}gcc")
set(CMAKE_CXX_COMPILER "${COMPILER}g++")

add_executable(test_client
	main.cpp
	BaseClient/BaseClient.cpp
)


set_target_properties(test_client PROPERTIES OUTPUT_NAME "${EXECUTABLE_NAME}")
