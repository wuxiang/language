include_directories(${TEST_DIR}/assistant/)
include_directories(${TEST_DIR}/DBfrontTest/)
FILE(GLOB_RECURSE ASSISTANT_SRC  ${TEST_DIR}/assistant/*.cpp)
FILE(GLOB_RECURSE FRONT_TEST_SRC  ${TEST_DIR}/DBfrontTest/*.cpp)


#add_executable(FIFOtest EXCLUDE_FROM_ALL fifotest.cpp 
add_executable(FIFOtest fifotest.cpp 
			 ${ASSISTANT_SRC}
			 ${FRONT_TEST_SRC}
			 ${GWTOOL_SRC}
			 ${FRONT_DIR}
			 ${FIFO_SRC})

target_link_libraries(FIFOtest pthread ${MYSQL_LIB_FILE})
