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

# Include any dependencies generated for this target.
include CMakeFiles/sap.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sap.dir/flags.make

qrc_main.cpp: ../ui/player.qml
qrc_main.cpp: ../assets/defaultBookCover.png
qrc_main.cpp: main.qrc.depends
qrc_main.cpp: ../main.qrc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating qrc_main.cpp"
	/usr/lib64/qt5/bin/rcc --name main --output /home/marvin/hello/C/SAP/Qml/build/qrc_main.cpp /home/marvin/hello/C/SAP/Qml/main.qrc

CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.o: sap_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.o -c /home/marvin/hello/C/SAP/Qml/build/sap_autogen/mocs_compilation.cpp

CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marvin/hello/C/SAP/Qml/build/sap_autogen/mocs_compilation.cpp > CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.i

CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marvin/hello/C/SAP/Qml/build/sap_autogen/mocs_compilation.cpp -o CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.s

CMakeFiles/sap.dir/src/sonic.c.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/src/sonic.c.o: ../src/sonic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/sap.dir/src/sonic.c.o"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sap.dir/src/sonic.c.o -c /home/marvin/hello/C/SAP/Qml/src/sonic.c

CMakeFiles/sap.dir/src/sonic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sap.dir/src/sonic.c.i"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marvin/hello/C/SAP/Qml/src/sonic.c > CMakeFiles/sap.dir/src/sonic.c.i

CMakeFiles/sap.dir/src/sonic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sap.dir/src/sonic.c.s"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marvin/hello/C/SAP/Qml/src/sonic.c -o CMakeFiles/sap.dir/src/sonic.c.s

CMakeFiles/sap.dir/src/Book.cpp.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/src/Book.cpp.o: ../src/Book.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sap.dir/src/Book.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sap.dir/src/Book.cpp.o -c /home/marvin/hello/C/SAP/Qml/src/Book.cpp

CMakeFiles/sap.dir/src/Book.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sap.dir/src/Book.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marvin/hello/C/SAP/Qml/src/Book.cpp > CMakeFiles/sap.dir/src/Book.cpp.i

CMakeFiles/sap.dir/src/Book.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sap.dir/src/Book.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marvin/hello/C/SAP/Qml/src/Book.cpp -o CMakeFiles/sap.dir/src/Book.cpp.s

CMakeFiles/sap.dir/src/AudioPlayer.cpp.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/src/AudioPlayer.cpp.o: ../src/AudioPlayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/sap.dir/src/AudioPlayer.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sap.dir/src/AudioPlayer.cpp.o -c /home/marvin/hello/C/SAP/Qml/src/AudioPlayer.cpp

CMakeFiles/sap.dir/src/AudioPlayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sap.dir/src/AudioPlayer.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marvin/hello/C/SAP/Qml/src/AudioPlayer.cpp > CMakeFiles/sap.dir/src/AudioPlayer.cpp.i

CMakeFiles/sap.dir/src/AudioPlayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sap.dir/src/AudioPlayer.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marvin/hello/C/SAP/Qml/src/AudioPlayer.cpp -o CMakeFiles/sap.dir/src/AudioPlayer.cpp.s

CMakeFiles/sap.dir/src/PlayerWindow.cpp.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/src/PlayerWindow.cpp.o: ../src/PlayerWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/sap.dir/src/PlayerWindow.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sap.dir/src/PlayerWindow.cpp.o -c /home/marvin/hello/C/SAP/Qml/src/PlayerWindow.cpp

CMakeFiles/sap.dir/src/PlayerWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sap.dir/src/PlayerWindow.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marvin/hello/C/SAP/Qml/src/PlayerWindow.cpp > CMakeFiles/sap.dir/src/PlayerWindow.cpp.i

CMakeFiles/sap.dir/src/PlayerWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sap.dir/src/PlayerWindow.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marvin/hello/C/SAP/Qml/src/PlayerWindow.cpp -o CMakeFiles/sap.dir/src/PlayerWindow.cpp.s

CMakeFiles/sap.dir/src/CoverProvider.cpp.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/src/CoverProvider.cpp.o: ../src/CoverProvider.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/sap.dir/src/CoverProvider.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sap.dir/src/CoverProvider.cpp.o -c /home/marvin/hello/C/SAP/Qml/src/CoverProvider.cpp

CMakeFiles/sap.dir/src/CoverProvider.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sap.dir/src/CoverProvider.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marvin/hello/C/SAP/Qml/src/CoverProvider.cpp > CMakeFiles/sap.dir/src/CoverProvider.cpp.i

CMakeFiles/sap.dir/src/CoverProvider.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sap.dir/src/CoverProvider.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marvin/hello/C/SAP/Qml/src/CoverProvider.cpp -o CMakeFiles/sap.dir/src/CoverProvider.cpp.s

CMakeFiles/sap.dir/src/ffmpegLiason.cpp.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/src/ffmpegLiason.cpp.o: ../src/ffmpegLiason.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/sap.dir/src/ffmpegLiason.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sap.dir/src/ffmpegLiason.cpp.o -c /home/marvin/hello/C/SAP/Qml/src/ffmpegLiason.cpp

CMakeFiles/sap.dir/src/ffmpegLiason.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sap.dir/src/ffmpegLiason.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marvin/hello/C/SAP/Qml/src/ffmpegLiason.cpp > CMakeFiles/sap.dir/src/ffmpegLiason.cpp.i

CMakeFiles/sap.dir/src/ffmpegLiason.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sap.dir/src/ffmpegLiason.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marvin/hello/C/SAP/Qml/src/ffmpegLiason.cpp -o CMakeFiles/sap.dir/src/ffmpegLiason.cpp.s

CMakeFiles/sap.dir/src/Global.cpp.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/src/Global.cpp.o: ../src/Global.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/sap.dir/src/Global.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sap.dir/src/Global.cpp.o -c /home/marvin/hello/C/SAP/Qml/src/Global.cpp

CMakeFiles/sap.dir/src/Global.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sap.dir/src/Global.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marvin/hello/C/SAP/Qml/src/Global.cpp > CMakeFiles/sap.dir/src/Global.cpp.i

CMakeFiles/sap.dir/src/Global.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sap.dir/src/Global.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marvin/hello/C/SAP/Qml/src/Global.cpp -o CMakeFiles/sap.dir/src/Global.cpp.s

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.o: ../ffmpeg/fftools/ffmpeg-main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.o -c /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg-main.cpp

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg-main.cpp > CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.i

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg-main.cpp -o CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.s

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.o: ../ffmpeg/fftools/ffmpeg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.o"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.o -c /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg.c

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.i"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg.c > CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.i

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.s"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg.c -o CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.s

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.o: ../ffmpeg/fftools/ffmpeg_opt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.o"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.o -c /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg_opt.c

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.i"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg_opt.c > CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.i

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.s"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg_opt.c -o CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.s

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.o: ../ffmpeg/fftools/ffmpeg_filter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.o"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.o -c /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg_filter.c

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.i"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg_filter.c > CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.i

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.s"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg_filter.c -o CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.s

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.o: ../ffmpeg/fftools/ffmpeg_hw.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.o"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.o -c /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg_hw.c

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.i"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg_hw.c > CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.i

CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.s"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/ffmpeg_hw.c -o CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.s

CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.o: ../ffmpeg/fftools/cmdutils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.o"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.o -c /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/cmdutils.c

CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.i"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/cmdutils.c > CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.i

CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.s"
	clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marvin/hello/C/SAP/Qml/ffmpeg/fftools/cmdutils.c -o CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.s

CMakeFiles/sap.dir/src/main.cpp.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/sap.dir/src/main.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sap.dir/src/main.cpp.o -c /home/marvin/hello/C/SAP/Qml/src/main.cpp

CMakeFiles/sap.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sap.dir/src/main.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marvin/hello/C/SAP/Qml/src/main.cpp > CMakeFiles/sap.dir/src/main.cpp.i

CMakeFiles/sap.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sap.dir/src/main.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marvin/hello/C/SAP/Qml/src/main.cpp -o CMakeFiles/sap.dir/src/main.cpp.s

CMakeFiles/sap.dir/qrc_main.cpp.o: CMakeFiles/sap.dir/flags.make
CMakeFiles/sap.dir/qrc_main.cpp.o: qrc_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/sap.dir/qrc_main.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sap.dir/qrc_main.cpp.o -c /home/marvin/hello/C/SAP/Qml/build/qrc_main.cpp

CMakeFiles/sap.dir/qrc_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sap.dir/qrc_main.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marvin/hello/C/SAP/Qml/build/qrc_main.cpp > CMakeFiles/sap.dir/qrc_main.cpp.i

CMakeFiles/sap.dir/qrc_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sap.dir/qrc_main.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marvin/hello/C/SAP/Qml/build/qrc_main.cpp -o CMakeFiles/sap.dir/qrc_main.cpp.s

# Object files for target sap
sap_OBJECTS = \
"CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/sap.dir/src/sonic.c.o" \
"CMakeFiles/sap.dir/src/Book.cpp.o" \
"CMakeFiles/sap.dir/src/AudioPlayer.cpp.o" \
"CMakeFiles/sap.dir/src/PlayerWindow.cpp.o" \
"CMakeFiles/sap.dir/src/CoverProvider.cpp.o" \
"CMakeFiles/sap.dir/src/ffmpegLiason.cpp.o" \
"CMakeFiles/sap.dir/src/Global.cpp.o" \
"CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.o" \
"CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.o" \
"CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.o" \
"CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.o" \
"CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.o" \
"CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.o" \
"CMakeFiles/sap.dir/src/main.cpp.o" \
"CMakeFiles/sap.dir/qrc_main.cpp.o"

# External object files for target sap
sap_EXTERNAL_OBJECTS =

../sap: CMakeFiles/sap.dir/sap_autogen/mocs_compilation.cpp.o
../sap: CMakeFiles/sap.dir/src/sonic.c.o
../sap: CMakeFiles/sap.dir/src/Book.cpp.o
../sap: CMakeFiles/sap.dir/src/AudioPlayer.cpp.o
../sap: CMakeFiles/sap.dir/src/PlayerWindow.cpp.o
../sap: CMakeFiles/sap.dir/src/CoverProvider.cpp.o
../sap: CMakeFiles/sap.dir/src/ffmpegLiason.cpp.o
../sap: CMakeFiles/sap.dir/src/Global.cpp.o
../sap: CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg-main.cpp.o
../sap: CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg.c.o
../sap: CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_opt.c.o
../sap: CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_filter.c.o
../sap: CMakeFiles/sap.dir/ffmpeg/fftools/ffmpeg_hw.c.o
../sap: CMakeFiles/sap.dir/ffmpeg/fftools/cmdutils.c.o
../sap: CMakeFiles/sap.dir/src/main.cpp.o
../sap: CMakeFiles/sap.dir/qrc_main.cpp.o
../sap: CMakeFiles/sap.dir/build.make
../sap: /usr/lib64/libavformat.so
../sap: /usr/lib64/libavcodec.so
../sap: /usr/lib64/libavutil.so
../sap: /usr/lib64/libswscale.so
../sap: /usr/lib64/libQt5Quick.so.5.15.2
../sap: /usr/lib64/libQt5Multimedia.so.5.15.2
../sap: /usr/lib64/libQt5Widgets.so.5.15.2
../sap: /usr/lib64/libQt5QmlModels.so.5.15.2
../sap: /usr/lib64/libQt5Qml.so.5.15.2
../sap: /usr/lib64/libQt5Network.so.5.15.2
../sap: /usr/lib64/libQt5Gui.so.5.15.2
../sap: /usr/lib64/libQt5Core.so.5.15.2
../sap: CMakeFiles/sap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marvin/hello/C/SAP/Qml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX executable ../sap"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sap.dir/build: ../sap

.PHONY : CMakeFiles/sap.dir/build

CMakeFiles/sap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sap.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sap.dir/clean

CMakeFiles/sap.dir/depend: qrc_main.cpp
	cd /home/marvin/hello/C/SAP/Qml/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marvin/hello/C/SAP/Qml /home/marvin/hello/C/SAP/Qml /home/marvin/hello/C/SAP/Qml/build /home/marvin/hello/C/SAP/Qml/build /home/marvin/hello/C/SAP/Qml/build/CMakeFiles/sap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sap.dir/depend
