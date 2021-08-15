cmake_minimum_required(VERSION 3.12)

project(sap)

# set(CMAKE_C_COMPILER gcc)

# list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_BUILD_TYPE Debug)

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



find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Gui Multimedia Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Gui Multimedia Widgets REQUIRED)
find_package(nlohmann_json REQUIRED)


set(SRC_LIST
    # ${CMAKE_SOURCE_DIR}/src/audiooutput-main.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/sonic.c
    ${CMAKE_SOURCE_DIR}/src/audiooutput.cpp
)

set(DEP_LIST
    ${CMAKE_SOURCE_DIR}/src/portaudio.h
    ${CMAKE_SOURCE_DIR}/src/sndfile.h
    ${CMAKE_SOURCE_DIR}/include/pa_asio.h
    ${CMAKE_SOURCE_DIR}/include/pa_jack.h
    ${CMAKE_SOURCE_DIR}/include/pa_linux_alsa.h
)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

set(QT_LIBS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::Widgets
)

set(LIB_LIST
    # ${CMAKE_SOURCE_DIR}/lib/libsonic.so
    ${CMAKE_SOURCE_DIR}/lib/libportaudio.so
    ${CMAKE_SOURCE_DIR}/lib/libsndfile.so
    ${QT_LIBS}
    nlohmann_json::nlohmann_json
)

set(BINARY_NAME "${PROJECT_NAME}")


add_executable(${BINARY_NAME} ${SRC_LIST} ${DEP_LIST})
target_compile_definitions(${BINARY_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${BINARY_NAME} ${LIB_LIST} dl)
