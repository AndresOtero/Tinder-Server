set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
add_definitions(-DBOOST_LOG_DYN_LINK=1)
FIND_PACKAGE(Threads)
FIND_PACKAGE(Boost COMPONENTS log log_setup thread filesystem system regex)

# Enable ExternalProject CMake module
include(ExternalProject)
# Download and install RocksDB

ExternalProject_Add(
    rocksdb
    URL https://github.com/facebook/rocksdb/archive/v4.4.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/rocksdb
    BUILD_IN_SOURCE 1
    BUILD_COMMAND make static_lib
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
add_library(applib STATIC ${APP_SOURCES} ${APP_HEADERS} src/services/match/MatchDAO.cpp src/services/match/MatchDAO.h src/services/chat/ChatServices.cpp src/services/chat/ChatServices.h src/model/Message.cpp src/model/Message.h src/services/match/MatchServices.cpp src/services/match/MatchServices.h src/services/authentication/AuthenticationException.cpp src/services/authentication/AuthenticationException.h src/dao/UserDAO.cpp src/dao/UserDAO.h src/dao/UserNotFoundException.cpp src/dao/UserNotFoundException.h src/model/Interest.cpp src/model/Interest.h src/services/match/NoMoreCandidatesException.cpp src/services/match/NoMoreCandidatesException.h)


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
file(GLOB_RECURSE APP_STATIC_LIBS  "lib/*.a")
set(GLOBAL_APP_STATIC_LIBS ${APP_STATIC_LIBS} PARENT_SCOPE)

SET_TARGET_PROPERTIES(applib PROPERTIES LINKER_LANGUAGE CXX)

find_package (BZip2)
if (BZIP2_FOUND)
  include_directories(${BZIP_INCLUDE_DIRS})
  target_link_libraries (applib ${BZIP2_LIBRARIES}) 
endif (BZIP2_FOUND)

find_package (ZLIB)
if (ZLIB_FOUND)
 include_directories(${ZLIB_INCLUDE_DIRS})
  target_link_libraries (applib ${ZLIB_LIBRARIES})

endif (ZLIB_FOUND)

target_link_libraries (applib
    curl
    myrocksdb
    cryptopp
    ${CMAKE_THREAD_LIBS_INIT} 
    ${Boost_LOG_SETUP_LIBRARY}
    ${Boost_LOG_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_REGEX_LIBRARY}
    pthread
    ${ZLIB_LIBRARIES}
    ${BZIP2_LIBRARIES}
    ${APP_STATIC_LIBS}
)

target_link_libraries (applib ) 

target_include_directories(applib PUBLIC "src")
target_compile_features(applib PRIVATE cxx_range_for)