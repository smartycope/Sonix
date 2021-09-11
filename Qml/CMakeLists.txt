cmake_minimum_required(VERSION 3.12)

######################################### Config ###############################################

# Set the project name
project(sap)

# Name the binary
set(BINARY_NAME "${PROJECT_NAME}")

# Set the build type
set(CMAKE_BUILD_TYPE Debug)

# Specify the compilers
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use carefully
set(IGNORED_COMPILER_WARNINGS
    -Wno-comment
    -Wno-macro-redefined
)

# Not sure what this does? I think it lets you include from header files in the directory you run make from?
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# This is for Qt stuff (I only have a vauge idea what they are or how they work)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# This is where all the cmake extensions are (files for find_package())
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/cmake)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.
# if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
# endif()

# No idea what this does or where it came from
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Specify where we want to put the binary once we build it. If there's a bin/ folder, this is where you specify it
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR})

# Put the specific binaries where I want them
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_DEBUG_OUTPUT_DIRECTORY   ${CMAKE_BINARY_DIR})

# To make everything fully multithreaded compliant
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Specify where the .qml files are located
set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/ui)

# Make Qt Creator aware of where the QML modules live
# set(_QML_IMPORT_PATHS "")

# Add new module paths here.
# list(APPEND _QML_IMPORT_PATHS ${CMAKE_SOURCE_DIR}/ui)

# set(QML_IMPORT_PATH
#     ${_QML_IMPORT_PATHS}
#     CACHE
#     STRING
#     "Path used to locate CMake modules by Qt Creator"
#     FORCE
# )

# Directories where Qt Creator can find QML files.
# (Not needed for builds, but makes Qt Creator code completion happy.)
list(APPEND QML_IMPORT_PATH "${CMAKE_SOURCE_DIR}/ui")

# Prevent adding duplicate values at each run of CMake.
list(REMOVE_DUPLICATES QML_IMPORT_PATH)

# The variable is cached in ${BUILD_DIR}/CMakeCache.txt. We need FORCE to
# change it there immediately. Also, add a comment to the cache file.
set(QML_IMPORT_PATH ${QML_IMPORT_PATH} CACHE STRING "Qt Creator 4.1 extra qml import paths" FORCE)


############################### Find dependancies ######################################

# Find dependancies
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Gui Multimedia Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Gui Multimedia Widgets REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(FFmpeg)


######################### Specify the stuff we need to build ################################

# Define source files
set(SRC_LIST
    ${CMAKE_SOURCE_DIR}/src/cope.hpp
    ${CMAKE_SOURCE_DIR}/src/sonic.c
    ${CMAKE_SOURCE_DIR}/src/Book.cpp
    ${CMAKE_SOURCE_DIR}/src/AudioPlayer.cpp
    ${CMAKE_SOURCE_DIR}/src/PlayerWindow.cpp
    ${CMAKE_SOURCE_DIR}/src/CoverProvider.cpp
    ${CMAKE_SOURCE_DIR}/src/ffmpegLiason.cpp
    ${CMAKE_SOURCE_DIR}/src/Global.cpp
    ${CMAKE_SOURCE_DIR}/ffmpeg/fftools/ffmpeg-main.cpp
    ${CMAKE_SOURCE_DIR}/ffmpeg/fftools/ffmpeg.c
    ${CMAKE_SOURCE_DIR}/ffmpeg/fftools/ffmpeg_opt.c
    ${CMAKE_SOURCE_DIR}/ffmpeg/fftools/ffmpeg_filter.c
    ${CMAKE_SOURCE_DIR}/ffmpeg/fftools/ffmpeg_hw.c
    ${CMAKE_SOURCE_DIR}/ffmpeg/fftools/cmdutils.c

    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# If you're lazy, and just want to build all the *.c files in a directory, use this
file(GLOB AUTO_SRC_LIST )

# Define the QT libaries we're using
set(QT_LIBS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::Widgets
)

# Define linked libraries
set(LIB_LIST
    # avfilter
    # avdevice swscale avformat avcodec swresample avutil
    ${FFMPEG_LIBRARIES}

    ${QT_LIBS}
    nlohmann_json::nlohmann_json
)

# Define the include directories
set(INC_DIRS
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/ffmpeg

    ${FFMPEG_INCLUDE_DIRS}
)

# Honestly not entirely sure what these are
set(LINK_DIRS )

# Define the QML UI files
set(QML_FILES
    "player.qml"
)

# Define the QT resources -- not used if you're using a .qrc file instead
set(QT_RESOURCES
    "defaultBookCover.png"
)

# Specify the .qrc files
set(QRC_FILES
    main.qrc
)


if(NOT ${FFMPEG_FOUND})
    list(APPEND LIB_LIST
        ${CMAKE_SOURCE_DIR}/lib/libavcodec.so
        ${CMAKE_SOURCE_DIR}/lib/libavdevice.so
        ${CMAKE_SOURCE_DIR}/lib/libavfilter.so
        ${CMAKE_SOURCE_DIR}/lib/libavformat.so
        ${CMAKE_SOURCE_DIR}/lib/libavresample.so
        ${CMAKE_SOURCE_DIR}/lib/libavutil.so
    )
endif()


######################### Actually build stuff ###############################
# Don't actually touch any of this stuff, unless you're removing QT from the project

# Ignore specific warnings
add_compile_options(${IGNORED_COMPILER_WARNINGS})

# Define where the libraries are located
include_directories(${INC_DIRS})

# Add the QT .qrc resources file
qt_add_resources(SRC_LIST ${QRC_FILES})

# Build the executable
if(ANDROID)
    add_library(${BINARY_NAME} SHARED ${SRC_LIST} ${AUTO_SRC_LIST})
else()
    add_executable(${BINARY_NAME} ${SRC_LIST} ${AUTO_SRC_LIST})
endif()

# Specify that it's an executable
set_target_properties(${BINARY_NAME} PROPERTIES WIN32_EXECUTABLE TRUE MACOSX_BUNDLE TRUE)

# Honestly not sure what this does...
link_directories(${BINARY_NAME} ${LINK_DIRS})

# Link the libraries
target_link_libraries(${BINARY_NAME} PUBLIC ${LIB_LIST} dl)

# Add the QT resources
# qt_add_resources(${BINARY_NAME} "ui" PREFIX "ui/" FILES ${QML_FILES}) # "qmake_immediate"
# qt5_add_resources(${BINARY_NAME} "" PREFIX "" FILES ${QT_RESOURCES})



# ffmpeg configure command:
# This is wrong, I believe
# ./configure --prefix=../ --bindir=bin --incdir=include --libdir=lib --shlibdir=../lib --arch=aarch64 --optflags='-O2 -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -fstack-protector-strong branch-protection=standard -fasynchronous-unwind-tables -fstack-clash-protection' --extra-ldflags='-Wl,-z,relro -Wl,--as-needed -Wl,-z,now' --extra-cflags=' -I/usr/include/rav1e' --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libvo-amrwbenc --enable-version3 --enable-bzlib --disable-crystalhd --enable-fontconfig --enable-frei0r --enable-gcrypt --enable-gnutls --enable-ladspa --enable-libaom --enable-libdav1d --enable-libass --enable-libbluray --enable-libcdio --enable-libdrm --enable-libjack --enable-libfreetype --enable-libfribidi --enable-libgsm --enable-liblensfun --enable-libmp3lame --enable-libmysofa --enable-nvenc --enable-openal --enable-opengl --enable-libopenjpeg --enable-libopenmpt --enable-libopus --enable-libpulse --enable-librsvg --enable-librav1e --enable-libsmbclient --enable-version3 --enable-libsoxr --enable-libspeex --enable-libssh --enable-libtheora --enable-libvorbis --enable-libv4l2 --enable-libvidstab --enable-libvpx --enable-vulkan --enable-libglslang --enable-libx264 --enable-libx265 --enable-libxvid --enable-libxml2 --enable-libzimg --enable-libzvbi --enable-lv2 --enable-avfilter --enable-libmodplug --enable-postproc --enable-pthreads --disable-static --enable-shared --enable-gpl --disable-debug --disable-stripping --shlibdir=/usr/lib64 --enable-lto --disable-nvenc --disable-logging --enable-gpl --enable-version3 --disable-ffplay --cxx=clang++ --cc=clang --disable-swresample
# I don't know what this one is
# ./configure --enable-gpl --enable-version3 --disable-ffplay --disable-doc --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libvo-amrwbenc --enable-version3 --enable-bzlib --disable-crystalhd --enable-fontconfig --enable-frei0r --enable-gcrypt --enable-gnutls --enable-ladspa --enable-libaom --enable-libdav1d --enable-libass --enable-libcdio --enable-libdrm --enable-libjack --enable-libfreetype --enable-libfribidi --enable-libgsm --enable-liblensfun --enable-libmp3lame --enable-libmysofa --enable-nvenc --enable-openal --enable-opencl --enable-opengl --enable-libopenjpeg --enable-libopenmpt --enable-libopus --enable-libpulse --enable-librsvg --enable-librav1e --enable-libsmbclient --enable-version3 --enable-libsoxr --enable-libspeex --enable-libssh --enable-libtheora --enable-libvorbis --enable-libv4l2 --enable-libvidstab --enable-libvpx --enable-vulkan --enable-libglslang --enable-libx264 --enable-libx265 --enable-libxvid --enable-libxml2 --enable-libzimg --enable-libzvbi --enable-lv2 --enable-avfilter --enable-libmodplug --enable-postproc --enable-pthreads --disable-static --enable-shared --enable-gpl --disable-debug --disable-stripping