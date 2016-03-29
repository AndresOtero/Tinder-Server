add_executable (server main.cpp)
include_directories (${APP_INCLUDE_DIRS})

target_link_libraries (server applib)
#add_dependencies(server applib)