# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wuxiang/language/cmake/cmake_example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wuxiang/language/cmake/cmake_example/build

# Include any dependencies generated for this target.
include CMakeFiles/tests_wo_exceptions_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tests_wo_exceptions_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tests_wo_exceptions_test.dir/flags.make

CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o: CMakeFiles/tests_wo_exceptions_test.dir/flags.make
CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o: ../tests_wo_exceptions.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/wuxiang/language/cmake/cmake_example/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o -c /home/wuxiang/language/cmake/cmake_example/tests_wo_exceptions.cpp

CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/wuxiang/language/cmake/cmake_example/tests_wo_exceptions.cpp > CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.i

CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/wuxiang/language/cmake/cmake_example/tests_wo_exceptions.cpp -o CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.s

CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o.requires:
.PHONY : CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o.requires

CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o.provides: CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o.requires
	$(MAKE) -f CMakeFiles/tests_wo_exceptions_test.dir/build.make CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o.provides.build
.PHONY : CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o.provides

CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o.provides.build: CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o
.PHONY : CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o.provides.build

# Object files for target tests_wo_exceptions_test
tests_wo_exceptions_test_OBJECTS = \
"CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o"

# External object files for target tests_wo_exceptions_test
tests_wo_exceptions_test_EXTERNAL_OBJECTS =

tests_wo_exceptions_test: CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o
tests_wo_exceptions_test: liboopl.a
tests_wo_exceptions_test: CMakeFiles/tests_wo_exceptions_test.dir/build.make
tests_wo_exceptions_test: CMakeFiles/tests_wo_exceptions_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable tests_wo_exceptions_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tests_wo_exceptions_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tests_wo_exceptions_test.dir/build: tests_wo_exceptions_test
.PHONY : CMakeFiles/tests_wo_exceptions_test.dir/build

CMakeFiles/tests_wo_exceptions_test.dir/requires: CMakeFiles/tests_wo_exceptions_test.dir/tests_wo_exceptions.cpp.o.requires
.PHONY : CMakeFiles/tests_wo_exceptions_test.dir/requires

CMakeFiles/tests_wo_exceptions_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tests_wo_exceptions_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tests_wo_exceptions_test.dir/clean

CMakeFiles/tests_wo_exceptions_test.dir/depend:
	cd /home/wuxiang/language/cmake/cmake_example/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wuxiang/language/cmake/cmake_example /home/wuxiang/language/cmake/cmake_example /home/wuxiang/language/cmake/cmake_example/build /home/wuxiang/language/cmake/cmake_example/build /home/wuxiang/language/cmake/cmake_example/build/CMakeFiles/tests_wo_exceptions_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tests_wo_exceptions_test.dir/depend

