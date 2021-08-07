cmake_minimum_required(VERSION 3.12)
# cmake_minimum_required(VERSION 3.5)

project(sap LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BINARY_NAME "${PROJECT_NAME}")

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
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

include_directories(${CMAKE_SOURCE_DIR}/lib)


# Find dependancies
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)


# Define source files
set(SRC_LIST
    ${CMAKE_SOURCE_DIR}/src/cope.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/PlayerWindow.cpp
    # ${CMAKE_SOURCE_DIR}/src/PlayerWindow.h
    ${CMAKE_SOURCE_DIR}/src/PlayerWindow.ui
    ${CMAKE_SOURCE_DIR}/src/Book.cpp

    ${CMAKE_SOURCE_DIR}/src/sonic.c
    ${CMAKE_SOURCE_DIR}/src/portaudio.h
    ${CMAKE_SOURCE_DIR}/src/sndfile.h
    ${CMAKE_SOURCE_DIR}/include/pa_asio.h
    ${CMAKE_SOURCE_DIR}/include/pa_jack.h
    ${CMAKE_SOURCE_DIR}/include/pa_linux_alsa.h
)

# Define linked libraries
set(LIB_LIST
    ${CMAKE_SOURCE_DIR}/lib/libsonic.so
    ${CMAKE_SOURCE_DIR}/lib/libportaudio.so
    ${CMAKE_SOURCE_DIR}/lib/libsndfile.so

    Qt${QT_VERSION_MAJOR}::Widgets
)

# Build the executable
if(ANDROID)
    add_library(${BINARY_NAME} SHARED ${SRC_LIST})
else()
    add_executable(${BINARY_NAME} ${SRC_LIST} ${DEP_LIST})
endif()

# Link the libraries
target_link_libraries(${BINARY_NAME} ${LIB_LIST} dl)
