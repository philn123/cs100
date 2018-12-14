CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)
ADD_EXECUTABLE(rshell 
            ${PROJECT_SOURCE_DIR}/src/main.cpp
            ${PROJECT_SOURCE_DIR}/src/command.cpp
            ${PROJECT_SOURCE_DIR}/src/And_Connector.cpp
            ${PROJECT_SOURCE_DIR}/src/Or_Connector.cpp
            ${PROJECT_SOURCE_DIR}/src/Semi_Connector.cpp
            ${PROJECT_SOURCE_DIR}/src/user.cpp
	    ${PROJECT_SOURCE_DIR}/src/Input_Redirect.cpp
	    ${PROJECT_SOURCE_DIR}/src/Output_Redirect.cpp
	    ${PROJECT_SOURCE_DIR}/src/Pipe.cpp
)
ADD_EXECUTABLE(test
            ${PROJECT_SOURCE_DIR}/src/command.cpp
            ${PROJECT_SOURCE_DIR}/tests/test_file.cpp
            ${PROJECT_SOURCE_DIR}/src/And_Connector.cpp
            ${PROJECT_SOURCE_DIR}/src/Or_Connector.cpp
            ${PROJECT_SOURCE_DIR}/src/Semi_Connector.cpp
            ${PROJECT_SOURCE_DIR}/src/user.cpp    
	    ${PROJECT_SOURCE_DIR}/src/Input_Redirect.cpp
	    ${PROJECT_SOURCE_DIR}/src/Output_Redirect.cpp
	    ${PROJECT_SOURCE_DIR}/src/Pipe.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
