cmake_minimum_required(VERSION 3.2.2)
project(tinder-server C CXX)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)


FIND_PACKAGE(Threads)



file(GLOB_RECURSE TINDER_SOURCES "src/*.cpp" "lib/*.cpp" "lib/*.c")
file(GLOB_RECURSE TINDER_HEADERS "src/*.h" "lib/*.h")
set (TINDER_INCLUDE_DIRS "")
foreach (_headerFile ${TINDER_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND TINDER_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES TINDER_INCLUDE_DIRS)
include_directories(${TINDER_INCLUDE_DIRS})



set(CMAKE_C_FLAGS "-DMG_ENABLE_THREADS")
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

add_executable (server ${TINDER_SOURCES})
TARGET_LINK_LIBRARIES ( server ${CMAKE_THREAD_LIBS_INIT} )