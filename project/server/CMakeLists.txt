add_executable (server main.cpp)
include_directories (${APP_INCLUDE_DIR})
target_link_libraries ( server applib)
