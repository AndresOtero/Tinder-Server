file(GLOB_RECURSE SRCS *.cpp)

add_executable(testapp ${SRCS} services/match/MatchDAOTest.cpp services/match/MatchDAOTest.h)

target_link_libraries(testapp
    applib
    libgtest
    libgmock
)

add_test(NAME testapp COMMAND testapp)
