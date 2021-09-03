cmake_minimum_required(VERSION 3.12)

project(sap)

# This stuff is all config

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

add_compile_options(-Wno-comment -Wno-macro-redefined)

set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR})

# Include dependancies
set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/ffmpeg)


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

set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/ui)
# Make Qt Creator aware of where the QML modules live
# set(_QML_IMPORT_PATHS "")

# ## Add new module paths here.
# list(APPEND _QML_IMPORT_PATHS ${CMAKE_SOURCE_DIR}/ui)

# set(QML_IMPORT_PATH
#     ${_QML_IMPORT_PATHS}
#     CACHE
#     STRING
#     "Path used to locate CMake modules by Qt Creator"
#     FORCE
# )

# End of config


# Specify the stuff we need to find and build

# Find dependancies
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Gui Multimedia Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Gui Multimedia Widgets REQUIRED)
find_package(nlohmann_json REQUIRED)

# Define the QT libaries we're using
set(QT_LIBS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::Widgets
)

# Define source files
set(SRC_LIST
    # ${CMAKE_SOURCE_DIR}/src/PlayerWindow.ui
    ${CMAKE_SOURCE_DIR}/src/cope.hpp
    ${CMAKE_SOURCE_DIR}/src/sonic.c
    ${CMAKE_SOURCE_DIR}/src/Book.cpp
    ${CMAKE_SOURCE_DIR}/src/AudioPlayer.cpp
    ${CMAKE_SOURCE_DIR}/src/PlayerWindow.cpp
    ${CMAKE_SOURCE_DIR}/src/CoverProvider.cpp
    ${CMAKE_SOURCE_DIR}/ffmpeg/ffmpeg.c

    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# Define linked libraries
set(LIB_LIST
    ${QT_LIBS}
    nlohmann_json::nlohmann_json
)

# Define the include directories
set(INC_DIRS
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/ffmpeg
)

# Define the QML UI files
set(QML_FILES
    "player.qml"
)

# Define the QT resources
set(RESOURCES
    "defaultBookCover.png"
)

# Done specifying and finding stuff


# Actually building things

# Define where the libraries are located
include_directories(${INC_DIRS})

# Add the QT .qrc resources file
qt_add_resources(SRC_LIST main.qrc)

# Build the executable
if(ANDROID)
    add_library(${BINARY_NAME} SHARED ${SRC_LIST})
else()
    add_executable(${BINARY_NAME} ${SRC_LIST})
endif()

# Specify that they're executables
set_target_properties(${BINARY_NAME} PROPERTIES WIN32_EXECUTABLE TRUE MACOSX_BUNDLE TRUE)

# Link the libraries
target_link_libraries(${BINARY_NAME} PUBLIC ${LIB_LIST} dl)

# Add the QT resources
# qt_add_resources(${BINARY_NAME} "ui" PREFIX "ui/" FILES ${QML_FILES}) # "qmake_immediate"
# qt5_add_resources(${BINARY_NAME} "" PREFIX "" FILES ${RESOURCES})

# Directories where Qt Creator can find QML files.
# (Not needed for builds, but makes Qt Creator code completion happy.)
list(APPEND QML_IMPORT_PATH "${CMAKE_SOURCE_DIR}/ui")
# Prevent adding duplicate values at each run of CMake.
list(REMOVE_DUPLICATES QML_IMPORT_PATH)
# The variable is cached in ${BUILD_DIR}/CMakeCache.txt. We need FORCE to
# change it there immediately. Also, add a comment to the cache file.
set(QML_IMPORT_PATH ${QML_IMPORT_PATH} CACHE STRING "Qt Creator 4.1 extra qml import paths" FORCE)



# set_source_files_properties(path/to/somewhere/MyFrame.qml PROPERTIES
#     QT_RESOURCE_ALIAS MyFrame.qml
# )

# qt_add_qml_module(someTarget
#     URI MyCo.Frames
#     RESOURCE_PREFIX /my.company.com/imports
#     QML_FILES
#         path/to/somewhere/MyFrame.qml
#         AnotherFrame.qml
# )
