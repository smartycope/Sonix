# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_SOURCE_DIR = /home/marvin/hello/C/SAP/Qml

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marvin/hello/C/SAP/Qml/build

# Utility rule file for sap_autogen.

# Include the progress variables for this target.
include CMakeFiles/sap_autogen.dir/progress.make

CMakeFiles/sap_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target sap"
	/usr/bin/cmake -E cmake_autogen /home/marvin/hello/C/SAP/Qml/build/CMakeFiles/sap_autogen.dir/AutogenInfo.json Debug

sap_autogen: CMakeFiles/sap_autogen
sap_autogen: CMakeFiles/sap_autogen.dir/build.make

.PHONY : sap_autogen

# Rule to build all files generated by this target.
CMakeFiles/sap_autogen.dir/build: sap_autogen

.PHONY : CMakeFiles/sap_autogen.dir/build

CMakeFiles/sap_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sap_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sap_autogen.dir/clean

CMakeFiles/sap_autogen.dir/depend:
	cd /home/marvin/hello/C/SAP/Qml/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marvin/hello/C/SAP/Qml /home/marvin/hello/C/SAP/Qml /home/marvin/hello/C/SAP/Qml/build /home/marvin/hello/C/SAP/Qml/build /home/marvin/hello/C/SAP/Qml/build/CMakeFiles/sap_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sap_autogen.dir/depend

