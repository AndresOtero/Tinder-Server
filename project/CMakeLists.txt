cmake_minimum_required (VERSION 3.2.2)

option(test "Build all tests." OFF)
project (tinder-server C CXX)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory (app) 
add_subdirectory (server) 

if(test)
	enable_testing ()
	add_subdirectory (test)
endif()

