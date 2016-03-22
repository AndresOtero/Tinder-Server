cmake_minimum_required (VERSION 3.2.2)

option(test "Build all tests." OFF)
project (tinder-server C CXX)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory (app) 
add_subdirectory (server) 

if(test)
	enable_testing ()
	SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
	SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
	SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
	add_subdirectory (test)
endif()
