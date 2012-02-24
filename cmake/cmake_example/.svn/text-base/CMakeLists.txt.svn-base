# This project name is OOP.
#
# Multiple projects can exist in a source tree.
#
# Among other things, this sets up convenience variables like OOP_SOURCE_DIR and
# OOP_BINARY_DIR.
project( OOP )

# In general, CMake has very good backwards compatibility.  But, you can make
# sure the person compiling your program has all features found in the CMake
# version you used.
cmake_minimum_required(VERSION 2.6)


# If doxygen exists, use the doc/CMakeLists.txt to generate code documentation.
find_package( Doxygen )
if( DOXYGEN_FOUND )
  # This is the directory that contains all the source files we want to have
  # documented.
  set( DOXYGEN_SOURCE_DIR ${OOP_SOURCE_DIR} )
  # This is the directory that holds the doxygen doxyfile template (doxy.conf.in)
  set( DOXYGEN_INPUT_DIR  ${OOP_SOURCE_DIR}/doc )
  # This is the directory where the generated code documentation goes.
  set( DOXYGEN_OUTPUT_DIR ${OOP_BINARY_DIR}/doc )
  # It is possible to put adddditional CMake commands in sub-directory
  # CMakeLists.txt, but the add_subdirectory command must be used to specify
  # which sub-directories should be scanned.
  add_subdirectory( doc )
else()
  message( WARNING "Doxygen not found - code documentation won't be created" )
endif()


# Directories passed to the include_directories() command will cause all the
# commands that require compilation, e.g. add_executable() or add_library(),
# which follow in the current CMakeLists.txt or sub-directory CMakeLists to have
# the given direction in the compilation command.
#
# For instance, it adds a -I<directory_name> to the gcc commands.
#
# Therefore, add directories with your own header files and header file
# directories of libraries that you use.
include_directories( ${OOP_SOURCE_DIR} )


# Add any new source files to this list.
set( OOP_SRC
  Animal.cpp
  Forest.cpp
  Organism.cpp
  Plant.cpp
  Time.cpp
  CppException.cpp 
  )
# Build the oop executable from the OOP_SRC source files.
add_executable( oop ${OOP_SRC} main.cpp )

# We can also easily make a library so people can just link to it.
add_library( oopl ${OOP_SRC} )

# Enable testing so we can add unit tests, and add the unit tests
enable_testing()

add_executable( unit_tests ${OOP_SOURCE_DIR}/unit_tests.cpp )
target_link_libraries( unit_tests oopl )
add_test( unit_tests unit_tests )

foreach( TEST_NAME exception plant animal time )
  add_executable( ${TEST_NAME}_test ${OOP_SOURCE_DIR}/${TEST_NAME}_test.cpp )
  target_link_libraries( ${TEST_NAME}_test oopl )
  add_test( ${TEST_NAME}_test ${TEST_NAME}_test )
endforeach()

add_executable( tests_wo_exceptions_test ${OOP_SOURCE_DIR}/tests_wo_exceptions.cpp )
target_link_libraries( tests_wo_exceptions_test oopl )
add_test( tests_wo_exceptions_test tests_wo_exceptions_test )

# Here is where we specify what gets installed and where.  If we make the
# destinations relative paths, they will be relative to the CMAKE_INSTALL_PREFIX
# configuration variable.
install( TARGETS oop oopl
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
# If someone wants to use the library, they will also need the headers.
string( REGEX REPLACE "[.]cpp" ".hpp;" OOP_HEADERS ${OOP_SRC} ) 
install( FILES ${OOP_HEADERS}
  DESTINATION include
  )
