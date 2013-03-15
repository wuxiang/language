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
set(FIFO_DIR ${PROJECT_SOURCE_DIR}/GW_fifo/)
set(GWTOOL_DIR ${PROJECT_SOURCE_DIR}/GW_tool/)
set(TEST_DIR   ${PROJECT_SOURCE_DIR}/GW_test/)
#set(CACHE_DIR ${PROJECT_SOURCE_DIR}/GW_front/)
set(FRONT_DIR ${PROJECT_SOURCE_DIR}/GW_front/)

#includ path
set(LOCAL_INCLUDE_DIR /usr/local/include)
set(OPT_INCLUDE_DIR /opt/local/include)

#mysql 
FIND_PATH(MYSQL_INCLUDE_DIR NAMES mysql.h my_sys.h my_global.h PATHS /usr/include/mysql/)

#include dir
include_directories(${LOCAL_INCLUDE_DIR})
include_directories(${OPT_INCLUDE_DIR})
include_directories(${MYSQL_INCLUDE_DIR})
include_directories(${FIFO_DIR})
include_directories(${GWTOOL_DIR})
include_directories(${FRONT_DIR})
#include_directories(${CACHE_DIR})

#source file 
FILE(GLOB_RECURSE FIFO_SRC  ${FIFO_DIR}/*.cpp)
FILE(GLOB_RECURSE GWTOOL_SRC  ${GWTOOL_DIR}/*.cpp)
FILE(GLOB_RECURSE FRONT_DIR  ${FRONT_DIR}/*.cpp)
#FILE(GLOB_RECURSE CACHE_DIR  ${CACHE_DIR}/*.cpp)

#set common lib
FIND_LIBRARY(MYSQL_LIB_FILE NAMES mysqlclient_r PATHS /usr/lib/mysql/)

set(LOCAL_LIB_DIR /usr/local/lib)
set(OPT_LIB_DIR /opt/local/lib)
link_directories(${LOCAL_LIB_DIR} ${OPT_LIB_DIR})

#add subdirectory
add_subdirectory(GW_test)
