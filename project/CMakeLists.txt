cmake_minimum_required(VERSION 3.2.2)
project(tinder-server)
file(GLOB_RECURSE TINDER_SOURCES "src/*.cpp")
file(GLOB_RECURSE TINDER_HEADERS "include/*.h")

set (TINDER_INCLUDE_DIRS "")
foreach (_headerFile ${TINDER_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND TINDER_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES TINDER_INCLUDE_DIRS)

include_directories(${TINDER_INCLUDE_DIRS})
add_executable (server ${TINDER_SOURCES})
