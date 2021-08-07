cmake_minimum_required(VERSION 3.14)

project(SonicPlaceholder LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)

# To make everything fully multithreaded compliant
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)


# put the binaries where I want them
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_DEBUG_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


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

#CONFIG += qmltypes

#set(QML_IMPORT_NAME Player)
#set(QML_IMPORT_MAJOR_VERSION 1)

#qt5_add_resources(qml_QRC src/qml.qrc)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Gui Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Gui Multimedia REQUIRED)
#find_package(LIBSNDFILE REQUIRED)


#qt5_add_resources(RESOURCES ${CMAKE_SOURCE_DIR}/assets/resources.qrc})


## Use pkg-config to get hints about paths
#find_package(PkgConfig QUIET)
#if(PKG_CONFIG_FOUND)
#    pkg_check_modules(LIBSNDFILE_PKGCONF sndfile)
#endif(PKG_CONFIG_FOUND)

## Include dir
#find_path(LIBSNDFILE_INCLUDE_DIR
#        NAMES sndfile.h
#        PATHS ${LIBSNDFILE_PKGCONF_INCLUDE_DIRS}
#        )

## Library
#find_library(LIBSNDFILE_LIBRARY
#        NAMES sndfile libsndfile-1
#        PATHS ${LIBSNDFILE_PKGCONF_LIBRARY_DIRS}
#        )

#find_package(PackageHandleStandardArgs)
#find_package_handle_standard_args(LibSndFile  DEFAULT_MSG  LIBSNDFILE_LIBRARY LIBSNDFILE_INCLUDE_DIR)

#if(LIBSNDFILE_FOUND)
#    set(LIBSNDFILE_LIBRARIES ${LIBSNDFILE_LIBRARY})
#    set(LIBSNDFILE_INCLUDE_DIRS ${LIBSNDFILE_INCLUDE_DIR})
#endif(LIBSNDFILE_FOUND)

#mark_as_advanced(LIBSNDFILE_LIBRARY LIBSNDFILE_LIBRARIES LIBSNDFILE_INCLUDE_DIR LIBSNDFILE_INCLUDE_DIRS)

#include(FindPkgConfig)
#pkg_search_module(SndFile REQUIRED sndfile)

#include_directories(${LIBSNDFILE_INCLUDE_DIRS})

##add_subdirectory(spectogram)
##add_executable(demo main.cpp)

#message(STATUS "sndfile include dirs path: ${LIBSNDFILE_INCLUDE_DIRS}")
#message(STATUS "sndfile libs path: ${LIBSNDFILE_LIBRARIES}")

##target_link_libraries (demo LINK_PUBLIC Spectrogram)
##target_link_libraries(demo PRIVATE ${LIBSNDFILE_LIBRARIES})


#set(PROJECT_SOURCES
#    ${CMAKE_SOURCE_DIR}/src/Player.cpp
#    ${CMAKE_SOURCE_DIR}/src/Book.cpp
#    ${CMAKE_SOURCE_DIR}/src/sonic.c
#    ${CMAKE_SOURCE_DIR}/main.qrc
#    ${CMAKE_SOURCE_DIR}/src/main.cpp
##    ${CMAKE_SOURCE_DIR}/sndfile.h
##    ${RESOURCES}
#)

set(PROJECT_SOURCES
    src/main.cpp
    src/Book.cpp
    src/Book.h
    src/Player.cpp
    src/Player.h
    src/cope.cpp
    src/cope.h
    main.qrc
)

if(ANDROID)
    add_library(SonicPlaceholder SHARED ${PROJECT_SOURCES})
else()
    add_executable(SonicPlaceholder ${PROJECT_SOURCES})
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

set(LIB_LIST
    ${CMAKE_SOURCE_DIR}/lib/libsonic.so.0.3.0
    ${CMAKE_SOURCE_DIR}/lib/libsndfile.so.1.0.32
#    /usr/lib/libsndfile.so.1
)

set(QT_LIBS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
)

#include_directories(${LIBSNDFILE_INCLUDE_DIRS})
#link_directories(${LIBSNDFILE_LIBRARY_DIRS})
#add_definitions(${LIBSNDFILE_DEFINITIONS})r

#set_target_properties(SonicPlaceholder PROPERTIES AUTOMOC ON)
#target_link_libraries(SonicPlaceholder PUBLIC Qt5::Core Qt5::Qml Qt5::Quick)
#target_include_directories(SonicPlaceholder PUBLIC include)

#target_link_libraries(SonicPlaceholder ${LIB_LIST} dl) # m dl

target_compile_definitions(SonicPlaceholder PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(SonicPlaceholder PRIVATE ${QT_LIBS} ${LIB_LIST} dl) # m dl
