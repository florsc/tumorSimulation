# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/163/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/163/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/florian/CLionProjects/tumorSimulation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/florian/CLionProjects/tumorSimulation/cmake-build-debug

# Include any dependencies generated for this target.
include _deps/json-build/test/CMakeFiles/test-modifiers.dir/depend.make
# Include the progress variables for this target.
include _deps/json-build/test/CMakeFiles/test-modifiers.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/json-build/test/CMakeFiles/test-modifiers.dir/flags.make

_deps/json-build/test/CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.o: _deps/json-build/test/CMakeFiles/test-modifiers.dir/flags.make
_deps/json-build/test/CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.o: _deps/json-src/test/src/unit-modifiers.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/florian/CLionProjects/tumorSimulation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/json-build/test/CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.o"
	cd /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.o -c /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-src/test/src/unit-modifiers.cpp

_deps/json-build/test/CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.i"
	cd /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-src/test/src/unit-modifiers.cpp > CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.i

_deps/json-build/test/CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.s"
	cd /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-src/test/src/unit-modifiers.cpp -o CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.s

# Object files for target test-modifiers
test__modifiers_OBJECTS = \
"CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.o"

# External object files for target test-modifiers
test__modifiers_EXTERNAL_OBJECTS = \
"/home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-build/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o"

_deps/json-build/test/test-modifiers: _deps/json-build/test/CMakeFiles/test-modifiers.dir/src/unit-modifiers.cpp.o
_deps/json-build/test/test-modifiers: _deps/json-build/test/CMakeFiles/doctest_main.dir/src/unit.cpp.o
_deps/json-build/test/test-modifiers: _deps/json-build/test/CMakeFiles/test-modifiers.dir/build.make
_deps/json-build/test/test-modifiers: _deps/json-build/test/CMakeFiles/test-modifiers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/florian/CLionProjects/tumorSimulation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-modifiers"
	cd /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-modifiers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/json-build/test/CMakeFiles/test-modifiers.dir/build: _deps/json-build/test/test-modifiers
.PHONY : _deps/json-build/test/CMakeFiles/test-modifiers.dir/build

_deps/json-build/test/CMakeFiles/test-modifiers.dir/clean:
	cd /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-build/test && $(CMAKE_COMMAND) -P CMakeFiles/test-modifiers.dir/cmake_clean.cmake
.PHONY : _deps/json-build/test/CMakeFiles/test-modifiers.dir/clean

_deps/json-build/test/CMakeFiles/test-modifiers.dir/depend:
	cd /home/florian/CLionProjects/tumorSimulation/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/florian/CLionProjects/tumorSimulation /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-src/test /home/florian/CLionProjects/tumorSimulation/cmake-build-debug /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-build/test /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/_deps/json-build/test/CMakeFiles/test-modifiers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/json-build/test/CMakeFiles/test-modifiers.dir/depend

