cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME MiddleFrame)
set(SERVER_NAME frame)

project(MIGRATION CXX C)
ENABLE_LANGUAGE(C)

#set compiler
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#flag
#-pg: produce run debug information
SET(CMAKE_C_FLAG "${CMAKE_C_FLAG} -Wall ")
SET(CMAKE_CXX_FLAG "${CMAKE_CXX_FLAG} -Wall ")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -o0 -Wall  -g -ggdb -std=c99 ")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -o0  -Wall -g -ggdb ")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -o3 -Wall ")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -o3 -Wall ")

#project file

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

#source file 
AUX_SOURCE_DIRECTORY(. PROJECT_SRC)

set(LOCAL_LIB_DIR /usr/local/lib)
set(OPT_LIB_DIR /opt/local/lib)
link_directories(${LOCAL_LIB_DIR} ${OPT_LIB_DIR})

#add subdirectory
#add_subdirectory(test EXCLUDE_FROM_ALL)

###################################################
##create excutable file
##################################################

add_executable(${SERVER_NAME}
			   ${PROJECT_SRC}
			   )

target_link_libraries(${SERVER_NAME} 
					pthread
					)
