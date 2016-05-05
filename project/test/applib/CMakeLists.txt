file(GLOB_RECURSE SRCS *.cpp)
find_package(Boost COMPONENTS regex system filesystem REQUIRED)
add_executable(testapp ${SRCS} services/match/MatchServicesTest.cpp services/match/MatchServicesTest.h)

target_link_libraries(testapp
    applib
    libgtest
    libgmock
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_REGEX_LIBRARY}
)

add_test(NAME testapp COMMAND testapp)
