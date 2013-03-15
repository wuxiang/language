include_directories(${TEST_DIR}/assistant/)
FILE(GLOB_RECURSE ASSISTANT_SRC  ${TEST_DIR}/assistant/*.cpp)


add_executable(FIFOtest EXCLUDE_FROM_ALL fifotest.cpp 
			 ${ASSISTANT_SRC}
			 ${GWTOOL_SRC}
			 ${FIFO_SRC})

target_link_libraries(FIFOtest pthread)
