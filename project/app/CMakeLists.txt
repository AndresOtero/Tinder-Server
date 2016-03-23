set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
add_definitions(-DBOOST_LOG_DYN_LINK=1)
FIND_PACKAGE(Threads)
FIND_PACKAGE(Boost COMPONENTS log log_setup thread filesystem system)

# Enable ExternalProject CMake module
include(ExternalProject)
# Download and install RocksDB

ExternalProject_Add(
    rocksdb
    BUILD_COMMAND make -j8 OPT="-DNDEBUG -O2" static_lib
    URL https://github.com/facebook/rocksdb/archive/v4.4.zip
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/rocksdb
    # Disable install step
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(rocksdb source_dir binary_dir)

# Create a librocksdb target to be used as a dependency by program
add_library(librocksdb IMPORTED STATIC GLOBAL)
add_dependencies(librocksdb rocksdb)

# Set rocksdb properties
MESSAGE( STATUS "rocksdblib:         " ${binary_dir}/librocksdb.a )
set_target_properties(librocksdb PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/librocksdb.a"
#    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
#include_directories("${source_dir}/include")




file(GLOB_RECURSE APP_SOURCES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE APP_HEADERS "src/*.h")
set(APP_INCLUDE_DIR src PARENT_SCOPE)

set (APP_INCLUDE_DIRS "")
foreach (_headerFile ${APP_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND APP_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES APP_INCLUDE_DIRS)

include_directories(${APP_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} )


set(CMAKE_C_FLAGS "-DMG_ENABLE_THREADS")

add_library(applib ${APP_SOURCES} ${APP_HEADERS})
add_dependencies(applib rocksdb)
target_include_directories(applib PUBLIC src)
SET_TARGET_PROPERTIES(applib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (applib
    ${CMAKE_THREAD_LIBS_INIT} 
    ${Boost_LOG_SETUP_LIBRARY}
    ${Boost_LOG_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}	
    z pthread rt librocksdb
)

