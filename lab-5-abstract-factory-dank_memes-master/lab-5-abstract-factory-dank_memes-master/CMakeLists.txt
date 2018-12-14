CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)
SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(testp
                testing_prints.cpp
                list_container.cpp
                vector_container.cpp
)
ADD_EXECUTABLE(example
                example.cpp
                list_container.cpp
                vector_container.cpp
)
TARGET_LINK_LIBRARIES(testp gtest)
