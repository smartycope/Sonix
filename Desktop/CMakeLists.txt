cmake_minimum_required(VERSION 3.12)
# cmake_minimum_required(VERSION 3.5)

# project(sap LANGUAGES CXX)
project(sap)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BINARY_NAME "${PROJECT_NAME}")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()
# list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_compile_options(-Wno-comment)

set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR})

# Include dependancies
set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)


# put the binaries where I want them
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#set(CMAKE_DEBUG_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug)

# To make everything fully multithreaded compliant
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)



# Find dependancies
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Gui Multimedia Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Gui Multimedia Widgets REQUIRED)
find_package(nlohmann_json REQUIRED)


# include(FetchContent)

# FetchContent_Declare(json
#   GIT_REPOSITORY https://github.com/nlohmann/json
#   GIT_TAG v3.7.3)

# FetchContent_GetProperties(json)
# if(NOT json_POPULATED)
#   FetchContent_Populate(json)
#   add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

# find_package(LIBVLC)
# find_library(AVCODEC_LIBRARY avcodec REQUIRED)

# find_package(LibAVCodec 53.35.0 REQUIRED)
# find_package(LibAVFormat 53.21.1 REQUIRED)
# find_package(LibAVUtil 51.22.1 REQUIRED)
# find_package(LibSndFile REQUIRED)
# find_package(Mpg123 REQUIRED)
# find_package(ni-media REQUIRED)
# find_package(Boost REQUIRED)
# find_package (LibAO REQUIRED)

set(QT_LIBS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::Widgets
)

# Define source files
set(SRC_LIST
    ${CMAKE_SOURCE_DIR}/src/PlayerWindow.ui
    ${CMAKE_SOURCE_DIR}/src/cope.hpp
    ${CMAKE_SOURCE_DIR}/src/PlayerWindow.cpp
    ${CMAKE_SOURCE_DIR}/src/Book.cpp
    ${CMAKE_SOURCE_DIR}/src/AudioPlayer.cpp
    ${CMAKE_SOURCE_DIR}/src/sonic.c

    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# Define linked libraries
set(LIB_LIST
    pthread
    # ${CMAKE_SOURCE_DIR}/lib/libsonic.so
    # ${CMAKE_SOURCE_DIR}/lib/libportaudio.so
    # /usr/lib64/libmp4v2.so
    # /usr/lib64/libfaad.so.2

    # /usr/lib64/libaudiodecoder.so
    # home/marvin/hello/C++/beatcleaver-winlib/win32lib-msvc90-release/
    # ${CMAKE_SOURCE_DIR}/lib/libsndfile.so
    # ${CMAKE_SOURCE_DIR}/lib/libaudiostream.a

    ${QT_LIBS}
    # ${LIBAVCODEC_LIBRARY}
    # ${LIBAVFORMAT_LIBRARY}
    # ${LIBAVUTIL_LIBRARY}
    # ${LIBAVCODEC_LIBRARIES}
    # ${LIBAVFORMAT_LIBRARIES}
    # ${LIBAVUTIL_LIBRARIES}

    # httplib::httplib
    nlohmann_json::nlohmann_json
    # ${BOOST_LIBRARIES}
    # ${LIBAO_LIBRARIES}

    # ${LIBVLC_LIBRARY}
    # ${LIBSNDFILE_LIBRARIES}
    # ${MPG123_LIBRARIES}

    # ${NI_MEDIA_LIBRARIES}
    # audiostream

    # avcodec-ffmpeg
    # avformat-ffmpeg

    # avcodec
    # avformat
    # avutil
    # swresample
)

# Define where the libraries are located
include_directories(
    ${CMAKE_SOURCE_DIR}/lib
    # home/marvin/hello/C++/beatcleaver-winlib/win32lib-msvc90-release/
    # /usr/include/mp4v2/
    # ${LIBVLC_INCLUDE_DIR}
    # ${LIBAVCODEC_INCLUDE_DIR}
    # ${LIBAVFORMAT_INCLUDE_DIR}
    # ${LIBAVUTIL_INCLUDE_DIR}
    # ${LIBSNDFILE_INCLUDE_DIRS}
    # ${MPG123_INCLUDE_DIRS}
    # ${NI_MEDIA_INCLUDE_DIRS}
    # ${BOOST_INCLUDE_DIRS}
    # audiostream
    # ${LIBAO_INCLUDE_DIR}
)

# link_directories (
    # home/marvin/hello/C++/beatcleaver-winlib/win32lib-msvc90-release/
# )
#     ${LIBAVCODEC_LIBRARY_DIRS}
#     ${LIBAVFORMAT_LIBRARY_DIRS}
#     ${LIBAVUTIL_LIBRARY_DIRS}
# )




# # __STDC_CONSTANT_MACROS is necessary for libav on Linux
# add_definitions (-D__STDC_CONSTANT_MACROS)

# list(APPEND bluecherry_client_LIBRARIES
#     ${LIBAVCODEC_LIBRARIES}
#     ${LIBAVFORMAT_LIBRARIES}
#     ${LIBAVUTIL_LIBRARIES}
# )

# get_filename_component(LIBAVCODEC_RPATH ${LIBAVCODEC_LIBRARY} PATH)
# get_filename_component(LIBAVFORMAT_RPATH ${LIBAVFORMAT_LIBRARY} PATH)
# get_filename_component(LIBAVUTIL_RPATH ${LIBAVUTIL_LIBRARY} PATH)

# if (LINUX)
#     set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${LIBAVCODEC_RPATH}")
#     set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${LIBAVCODEC_LIBAVFORMAT}")
#     set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${LIBAVUTIL_RPATH}")
# endif (LINUX)




# Build the executable
if(ANDROID)
    add_library(${BINARY_NAME} SHARED ${SRC_LIST})
else()
    add_executable(${BINARY_NAME} ${SRC_LIST})
endif()

# Link the libraries
target_link_libraries(${BINARY_NAME} ${LIB_LIST} dl)



























# make[1]: Entering directory '/home/marvin/hello/C/faad2/libfaad'
# make[2]: Entering directory '/home/marvin/hello/C/faad2/libfaad'
#  /bin/mkdir -p '/usr/local/lib'
#  /bin/mkdir -p '/usr/local/include'
#  /bin/mkdir -p '/usr/local/lib/pkgconfig'
#  /bin/sh ../libtool   --mode=install /bin/install -c   libfaad.la libfaad_drm.la '/usr/local/lib'
#  /bin/install -c -m 644 ../include/faad.h ../include/neaacdec.h '/usr/local/include'
#  /bin/install -c -m 644 faad2.pc '/usr/local/lib/pkgconfig'
# libtool: install: /bin/install -c .libs/libfaad.so.2.0.0 /usr/local/lib/libfaad.so.2.0.0
# libtool: install: (cd /usr/local/lib && { ln -s -f libfaad.so.2.0.0 libfaad.so.2 || { rm -f libfaad.so.2 && ln -s libfaad.so.2.0.0 libfaad.so.2; }; })
# libtool: install: (cd /usr/local/lib && { ln -s -f libfaad.so.2.0.0 libfaad.so || { rm -f libfaad.so && ln -s libfaad.so.2.0.0 libfaad.so; }; })
# libtool: install: /bin/install -c .libs/libfaad.lai /usr/local/lib/libfaad.la
# libtool: install: /bin/install -c .libs/libfaad_drm.so.2.0.0 /usr/local/lib/libfaad_drm.so.2.0.0
# libtool: install: (cd /usr/local/lib && { ln -s -f libfaad_drm.so.2.0.0 libfaad_drm.so.2 || { rm -f libfaad_drm.so.2 && ln -s libfaad_drm.so.2.0.0 libfaad_drm.so.2; }; })
# libtool: install: (cd /usr/local/lib && { ln -s -f libfaad_drm.so.2.0.0 libfaad_drm.so || { rm -f libfaad_drm.so && ln -s libfaad_drm.so.2.0.0 libfaad_drm.so; }; })
# libtool: install: /bin/install -c .libs/libfaad_drm.lai /usr/local/lib/libfaad_drm.la
# libtool: install: /bin/install -c .libs/libfaad.a /usr/local/lib/libfaad.a
# libtool: install: chmod 644 /usr/local/lib/libfaad.a
# libtool: install: ranlib /usr/local/lib/libfaad.a
# libtool: install: /bin/install -c .libs/libfaad_drm.a /usr/local/lib/libfaad_drm.a
# libtool: install: chmod 644 /usr/local/lib/libfaad_drm.a
# libtool: install: ranlib /usr/local/lib/libfaad_drm.a
# libtool: finish: PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/var/lib/snapd/snap/bin:/sbin" ldconfig -n /usr/local/lib
# ----------------------------------------------------------------------
# Libraries have been installed in:
#    /usr/local/lib

# If you ever happen to want to link against installed libraries
# in a given directory, LIBDIR, you must either use libtool, and
# specify the full pathname of the library, or use the '-LLIBDIR'
# flag during linking and do at least one of the following:
#    - add LIBDIR to the 'LD_LIBRARY_PATH' environment variable
#      during execution
#    - add LIBDIR to the 'LD_RUN_PATH' environment variable
#      during linking
#    - use the '-Wl,-rpath -Wl,LIBDIR' linker flag
#    - have your system administrator add LIBDIR to '/etc/ld.so.conf'

# See any operating system documentation about shared libraries for
# more information, such as the ld(1) and ld.so(8) manual pages.
# ----------------------------------------------------------------------
