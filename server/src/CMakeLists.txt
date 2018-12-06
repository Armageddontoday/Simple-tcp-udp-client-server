cmake_minimum_required(VERSION 2.6)
project(test_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_C_COMPILER "${COMPILER}gcc")
set(CMAKE_CXX_COMPILER "${COMPILER}g++")

add_executable(test_server
	main.cpp
	RequestHandler/RequestHandler.cpp
	BaseServer/BaseServer.cpp
)

set_target_properties(test_server PROPERTIES OUTPUT_NAME "${EXECUTABLE_NAME}")
