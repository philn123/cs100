CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(tests
    test.cpp
    iterator.cpp
    composite.cpp
)
TARGET_LINK_LIBRARIES(tests gtest)
