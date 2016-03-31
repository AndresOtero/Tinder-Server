
add_executable (server main.cpp)
include_directories (${APP_INCLUDE_DIRS})

message(STATUS "libs ${GLOBAL_APP_STATIC_LIBS}")
target_link_libraries (server  applib)