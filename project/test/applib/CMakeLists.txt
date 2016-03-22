file(GLOB_RECURSE SRCS *.cpp)

add_executable(testapp ${SRCS})

target_link_libraries(testapp
    applib
    libgtest
    libgmock
)

add_test(NAME testapp COMMAND testapp)
