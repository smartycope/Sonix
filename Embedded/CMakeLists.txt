cmake_minimum_required(VERSION 3.12)

project(sap)

# set(CMAKE_C_COMPILER   clang)
# set(CMAKE_CXX_COMPILER clang++)

# list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-Wno-comment)
# add_compile_options(-Wno-macro-redfine)

set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR})

# Include dependancies
set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# set(CMAKE_PREFIX_PATH /usr/lib64/)


# put the binaries where I want them
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#set(CMAKE_DEBUG_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug)

# To make everything fully multithreaded compliant
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -DUSE_DEV_LIB")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)


# find_package(Curses REQUIRED)
# find_package(libmp4v2 REQUIRED)
# find_package(SndFile REQUIRED)
# include(AndroidApk)
find_package(Portaudio REQUIRED)

####################### Find SNDFILE#####################
# - Try to find libsndfile
# Once done, this will define
#
#  LIBSNDFILE_FOUND - system has libsndfile
#  LIBSNDFILE_INCLUDE_DIRS - the libsndfile include directories
#  LIBSNDFILE_LIBRARIES - link these to use libsndfile

# Use pkg-config to get hints about paths
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(LIBSNDFILE_PKGCONF sndfile)
endif(PKG_CONFIG_FOUND)

# Include dir
find_path(LIBSNDFILE_INCLUDE_DIR
        NAMES sndfile.h
        PATHS ${LIBSNDFILE_PKGCONF_INCLUDE_DIRS}
        )

# Library
find_library(LIBSNDFILE_LIBRARY
        NAMES sndfile libsndfile-1
        PATHS ${LIBSNDFILE_PKGCONF_LIBRARY_DIRS}
        )

find_package(PackageHandleStandardArgs)
find_package_handle_standard_args(LibSndFile  DEFAULT_MSG  LIBSNDFILE_LIBRARY LIBSNDFILE_INCLUDE_DIR)

if(LIBSNDFILE_FOUND)
    set(LIBSNDFILE_LIBRARIES ${LIBSNDFILE_LIBRARY})
    set(LIBSNDFILE_INCLUDE_DIRS ${LIBSNDFILE_INCLUDE_DIR})
endif(LIBSNDFILE_FOUND)

mark_as_advanced(LIBSNDFILE_LIBRARY LIBSNDFILE_LIBRARIES LIBSNDFILE_INCLUDE_DIR LIBSNDFILE_INCLUDE_DIRS)

include(FindPkgConfig)
pkg_search_module(SndFile REQUIRED sndfile)

# include_directories(${LIBSNDFILE_INCLUDE_DIRS})

##############################################################

if(LIBSNDFILE_FOUND)
    message(STATUS "sndfile found!")
    message(STATUS "sndfile include dirs path: ${LIBSNDFILE_INCLUDE_DIRS}")
    message(STATUS "sndfile libs path: ${LIBSNDFILE_LIBRARIES}")
endif(LIBSNDFILE_FOUND)

if(PORTAUDIO_FOUND)
    message(STATUS "portaudio found!")
    message(STATUS "portaudio include dirs path: ${PORTAUDIO_INCLUDE_DIRS}")
    message(STATUS "portaudio libs path: ${PORTAUDIO_LIBRARIES}")
endif(PORTAUDIO_FOUND)


set(SRC_LIST
    ${CMAKE_SOURCE_DIR}/src/cope.cpp
    ${CMAKE_SOURCE_DIR}/src/portaudio.h
    ${CMAKE_SOURCE_DIR}/src/sndfile.h
    ${CMAKE_SOURCE_DIR}/src/sonic.c
    ${CMAKE_SOURCE_DIR}/include/pa_asio.h
    ${CMAKE_SOURCE_DIR}/include/pa_jack.h
    ${CMAKE_SOURCE_DIR}/include/pa_linux_alsa.h
    ${CMAKE_SOURCE_DIR}/src/font12.c
    ${CMAKE_SOURCE_DIR}/src/font12CN.c
    ${CMAKE_SOURCE_DIR}/src/font16.c
    ${CMAKE_SOURCE_DIR}/src/font20.c
    ${CMAKE_SOURCE_DIR}/src/font24.c
    ${CMAKE_SOURCE_DIR}/src/font24CN.c
    ${CMAKE_SOURCE_DIR}/src/font8.c
    ${CMAKE_SOURCE_DIR}/src/DEV_Config.c
    ${CMAKE_SOURCE_DIR}/src/GUI_Paint.c
    ${CMAKE_SOURCE_DIR}/src/GUI_BMP.c
    ${CMAKE_SOURCE_DIR}/src/dev_hardware_SPI.c
    ${CMAKE_SOURCE_DIR}/src/sysfs_gpio.c
    ${CMAKE_SOURCE_DIR}/src/LCD_1in3.c
    ${CMAKE_SOURCE_DIR}/src/Book.cpp
    ${CMAKE_SOURCE_DIR}/src/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/Menu.h
    ${CMAKE_SOURCE_DIR}/src/BluetoothMenu.cpp
    ${CMAKE_SOURCE_DIR}/src/FileMenu.cpp
    ${CMAKE_SOURCE_DIR}/src/PlayerMenu.cpp
    ${CMAKE_SOURCE_DIR}/src/Settings.cpp
    ${CMAKE_SOURCE_DIR}/src/SettingsMenu.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# file(GLOB SRC_LIST ${CMAKE_SOURCE_DIR}/src/*.c*) # ${CMAKE_SOURCE_DIR}/src/*.h*)
# AUX_SOURCE_DIRECTORY(/src VARIABLE)
message(STATUS "Building these files:\n ${SRC_LIST}")

# set(DEP_LIST
#     ${CMAKE_SOURCE_DIR}/src/portaudio.h
#     ${CMAKE_SOURCE_DIR}/src/sndfile.h
#     ${CMAKE_SOURCE_DIR}/include/pa_asio.h
#     ${CMAKE_SOURCE_DIR}/include/pa_jack.h
#     ${CMAKE_SOURCE_DIR}/include/pa_linux_alsa.h
# )

include_directories(
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${LIBSNDFILE_INCLUDE_DIRS}
    ${PORTAUDIO_INCLUDE_DIRS}
    # ${CURSES_INCLUDE_DIR}
    # ${LIBMP4V2_INCLUDE_DIR}
    # /usr/include/mp4v2/
)

set(LIB_LIST
    ${CMAKE_SOURCE_DIR}/lib/libsonic.so
    # ${CMAKE_SOURCE_DIR}/lib/libportaudio.so
    # ${CMAKE_SOURCE_DIR}/lib/libsndfile.so
    # ${CURSES_LIBRARIES}
    ${LIBSNDFILE_LIBRARIES}
    ${PORTAUDIO_LIBRARIES}
    m
    # wiringPi
    # ${LIBMP4V2_LIBRARIES}
    # /usr/lib64/libmp4v2.so
)

set(BINARY_NAME "${PROJECT_NAME}")

add_executable(${BINARY_NAME} ${SRC_LIST}) # ${DEP_LIST})
# set_target_properties(${BINARY_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

target_link_libraries(${BINARY_NAME} ${LIB_LIST} dl)
