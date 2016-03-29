set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
add_definitions(-DBOOST_LOG_DYN_LINK=1)
FIND_PACKAGE(Threads)
FIND_PACKAGE(Boost COMPONENTS log log_setup thread filesystem system)

# Enable ExternalProject CMake module
include(ExternalProject)
# Download and install RocksDB

ExternalProject_Add(
    rocksdb
    URL https://github.com/facebook/rocksdb/archive/v4.4.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/rocksdb
    BUILD_IN_SOURCE 1
    BUILD_COMMAND make -j8 OPT="-DNDEBUG -O2" static_lib
    CONFIGURE_COMMAND ""
    # Disable install step
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(rocksdb source_dir)
ExternalProject_Get_Property(rocksdb binary_dir)


# Create a librocksdb target to be used as a dependency by program
add_library(myrocksdb STATIC IMPORTED)
add_dependencies(myrocksdb rocksdb)

set_property(TARGET rocksdb PROPERTY IMPORTED_LOCATION ${LIBROCKSDB_A})
# Set rocksdb properties

file(MAKE_DIRECTORY "${source_dir}/include")
set_target_properties(myrocksdb PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/librocksdb.a"
    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
)

set(ROCKSDB_SRC "${source_dir}/include")
include_directories(${ROCKSDB_SRC})



set(CMAKE_C_FLAGS "-DMG_ENABLE_THREADS")

file(GLOB_RECURSE APP_SOURCES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE APP_HEADERS "src/*.h")
add_library(applib STATIC ${APP_SOURCES} ${APP_HEADERS})







#set(APP_INCLUDE_DIR src PARENT_SCOPE)
#file(GLOB LIBS "${CMAKE_SOURCE_DIR}/app/lib/*.a")
#set(APP_LIBS ${LIBS} PARENT_SCOPE)

set (APP_INCLUDE_DIRS "" PARENT_SCOPE)
foreach (_headerFile ${APP_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND APP_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES APP_INCLUDE_DIRS)

target_include_directories(applib PUBLIC ${APP_INCLUDE_DIRS})
target_INCLUDE_DIRECTORIES(applib PRIVATE ${Boost_INCLUDE_DIRS} )
target_INCLUDE_DIRECTORIES(applib PRIVATE ${ROCKSDB_SRC} )


add_dependencies(applib myrocksdb)

SET_TARGET_PROPERTIES(applib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (applib
    ${CMAKE_THREAD_LIBS_INIT} 
    ${Boost_LOG_SETUP_LIBRARY}
    ${Boost_LOG_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
 #   ${LIBS}
    z pthread rt myrocksdb
)

target_include_directories(applib PUBLIC "src")
