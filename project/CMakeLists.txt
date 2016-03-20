cmake_minimum_required(VERSION 3.2.2)
project(tinder-server C CXX)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
add_definitions(-DBOOST_LOG_DYN_LINK=1)

FIND_PACKAGE(Threads)

FIND_PACKAGE(Boost COMPONENTS log log_setup thread filesystem system)

file(GLOB_RECURSE TINDER_SOURCES "src/*.cpp" "lib/*.cpp" "lib/*.c")
file(GLOB_RECURSE TINDER_HEADERS "src/*.h" "lib/*.h")
file(GLOB_RECURSE TINDER_STATICS "lib/*.a")
set (TINDER_INCLUDE_DIRS "")
foreach (_headerFile ${TINDER_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND TINDER_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES TINDER_INCLUDE_DIRS)
include_directories(${TINDER_INCLUDE_DIRS})


INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} )



set(CMAKE_C_FLAGS "-DMG_ENABLE_THREADS")
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

add_executable (server ${TINDER_SOURCES})
target_link_libraries ( server
	${TINDER_STATICS} 
    ${CMAKE_THREAD_LIBS_INIT} 
    ${Boost_LOG_SETUP_LIBRARY}
    ${Boost_LOG_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)
