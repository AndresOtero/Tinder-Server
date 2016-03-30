cmake_minimum_required (VERSION 3.2.2)

option(test "Build all tests." ON)
project (tinder-server C CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#SET(CMAKE_SHARED_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")
#SET(CMAKE_EXE_LINKER_FLAGS="--coverage")

set(CMAKE_CXX_STANDARD 11)
if(test)
	include(CodeCoverage)
	SET(CMAKE_CXX_FLAGS "-g -O0 -Wall --coverage")
	SET(CMAKE_C_FLAGS "-g -O0 -Wall -W --coverage")
	SET(CMAKE_EXE_LINKER_FLAGS "--coverage")
    SETUP_TARGET_FOR_COVERAGE(
				coverage  # Name for custom target.
				testapp         # Name of the test driver executable that runs the tests.
				coverage-report            # Name of output directory.
				)
endif()


add_subdirectory (app) 
add_subdirectory (server) 

if(test)
	enable_testing ()
	add_subdirectory (test)
endif()
