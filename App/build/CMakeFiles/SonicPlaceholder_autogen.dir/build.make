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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rebecca/hello/C++/SAP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rebecca/hello/C++/SAP/build

# Utility rule file for SonicPlaceholder_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/SonicPlaceholder_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SonicPlaceholder_autogen.dir/progress.make

CMakeFiles/SonicPlaceholder_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/rebecca/hello/C++/SAP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target SonicPlaceholder"
	/usr/bin/cmake -E cmake_autogen /home/rebecca/hello/C++/SAP/build/CMakeFiles/SonicPlaceholder_autogen.dir/AutogenInfo.json Debug

SonicPlaceholder_autogen: CMakeFiles/SonicPlaceholder_autogen
SonicPlaceholder_autogen: CMakeFiles/SonicPlaceholder_autogen.dir/build.make
.PHONY : SonicPlaceholder_autogen

# Rule to build all files generated by this target.
CMakeFiles/SonicPlaceholder_autogen.dir/build: SonicPlaceholder_autogen
.PHONY : CMakeFiles/SonicPlaceholder_autogen.dir/build

CMakeFiles/SonicPlaceholder_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SonicPlaceholder_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SonicPlaceholder_autogen.dir/clean

CMakeFiles/SonicPlaceholder_autogen.dir/depend:
	cd /home/rebecca/hello/C++/SAP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rebecca/hello/C++/SAP /home/rebecca/hello/C++/SAP /home/rebecca/hello/C++/SAP/build /home/rebecca/hello/C++/SAP/build /home/rebecca/hello/C++/SAP/build/CMakeFiles/SonicPlaceholder_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SonicPlaceholder_autogen.dir/depend
