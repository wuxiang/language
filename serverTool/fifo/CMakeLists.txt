cmake_minimum_required(VERSION 2.8)

#set compiler
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(DBfront)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#flag
SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -Wall)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -o0 -Wall  -g -ggdb")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -o0  -Wall -g -ggdb")

SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -o3 -Wall")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -o3 -Wall")

#project
set(FIFO_DIR ${PROJECT_SOURCE_DIR}/fifo/)
set(GWTOOL_DIR ${PROJECT_SOURCE_DIR}/GWTool/)
set(TEST_DIR   ${PROJECT_SOURCE_DIR}/test/)

#includ path
set(LOCAL_INCLUDE_DIR /usr/local/include)
set(OPT_INCLUDE_DIR /opt/local/include)

#include dir
include_directories(${LOCAL_INCLUDE_DIR})
include_directories(${OPT_INCLUDE_DIR})
include_directories(${FIFO_DIR})
include_directories(${GWTOOL_DIR})

#source file 
FILE(GLOB_RECURSE FIFO_SRC  ${FIFO_DIR}/*.cpp)
FILE(GLOB_RECURSE GWTOOL_SRC  ${GWTOOL_DIR}/*.cpp)

#set common lib
set(LOCAL_LIB_DIR /usr/local/lib)
set(OPT_LIB_DIR /opt/local/lib)
link_directories(${LOCAL_LIB_DIR} ${OPT_LIB_DIR})

#add subdirectory
add_subdirectory(test)
