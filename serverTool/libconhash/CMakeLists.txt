cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME ConsistcyHash)
set(TEST_NAME consistcy)

project(HttpStore CXX C)
ENABLE_LANGUAGE(C)

#set compiler
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#flag
SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -Wall)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -o0 -Wall  -g -ggdb")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -o0  -Wall -g -ggdb")

SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -o3 -Wall")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -o3 -Wall")

#includ path
set(LOCAL_INCLUDE_DIR /usr/local/include)
set(OPT_INCLUDE_DIR /opt/local/include)

#64-byte machine
set(LIB64_DIR /lib64)
set(USR_LIB64_DIR  /usr/lib64)
set(LOCAL_LIB64_DIR /usr/local/lib64)

#include dir
include_directories(${LOCAL_INCLUDE_DIR})
include_directories(${OPT_INCLUDE_DIR})
include_directories(${LIB64_DIR})
include_directories(${USR_LIB64_DIR})
include_directories(${LOCAL_LIB64_DIR})
include_directories(${PROJECT_SOURCE_DIR})

#source file 
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

set(LOCAL_LIB_DIR /usr/local/lib)
set(OPT_LIB_DIR /opt/local/lib)
link_directories(${LOCAL_LIB_DIR} ${OPT_LIB_DIR})

###################################################
##create excutable file
##################################################

add_executable(${TEST_NAME}
			   ${DIR_SRCS}
			   )

target_link_libraries(${TEST_NAME} pthread)
