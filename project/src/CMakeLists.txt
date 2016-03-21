set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
add_definitions(-DBOOST_LOG_DYN_LINK=1)
FIND_PACKAGE(Threads)
FIND_PACKAGE(Boost COMPONENTS log log_setup thread filesystem system)

file(GLOB_RECURSE APP_SOURCES "app/*.cpp" "lib/*.cpp" "lib/*.c")
file(GLOB_RECURSE APP_HEADERS "app/*.h" "lib/*.h")


set (APP_INCLUDE_DIRS "")
foreach (_headerFile ${APP_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND APP_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES APP_INCLUDE_DIRS)

include_directories(${APP_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} )

set(CMAKE_C_FLAGS "-DMG_ENABLE_THREADS")
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

add_library(applib ${APP_SOURCES} ${APP_HEADERS})
SET_TARGET_PROPERTIES(applib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (applib
	${TINDER_STATICS} 
    ${CMAKE_THREAD_LIBS_INIT} 
    ${Boost_LOG_SETUP_LIBRARY}
    ${Boost_LOG_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)
add_executable (server main.cpp)
target_link_libraries(server applib)

