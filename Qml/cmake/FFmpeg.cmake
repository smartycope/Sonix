
# set(FFMPEG_CONFIGURE_COMMAND
#     configure
#     --prefix=${CMAKE_SOURCE_DIR}/ffmpeg
#     --libdir=${CMAKE_SOURCE_DIR}/libs
#     --shlibdir=${CMAKE_SOURCE_DIR}/libs
#     --enable-gpl
#     --enable-version3
#     --disable-static
#     --enable-shared
#     --disable-programs
#     --disable-ffplay
#     --enable-avresample
#     --disable-doc
#     --cc=${CMAKE_C_COMPILER}
#     --cxx=${CMAKE_CXX_COMPILER}
#     --disable-debug
# )


set(FFMPEG_CONFIGURE_COMMAND
    configure --prefix=${CMAKE_SOURCE_DIR}/ffmpeg --libdir=${CMAKE_SOURCE_DIR}/libs --shlibdir=${CMAKE_SOURCE_DIR}/libs --enable-gpl --enable-version3 --disable-static --enable-shared --disable-programs --disable-ffplay --enable-avresample --disable-doc --cc=${CMAKE_C_COMPILER} --cxx=${CMAKE_CXX_COMPILER} --disable-debug
)


# --quiet
# --incdir=${CMAKE_SOURCE_DIR}/include
# --host-os=${}
# --arch=${}
# --target-os=${}
# --toolchain=

set(FFMPEG_BUILD_DIR ${CMAKE_BINARY_DIR}/build/ffmpegBuild)

# set_property(DIRECTORY PROPERTY EP_STEP_TARGETS build)
ExternalProject_Add(FFmpeg
    URL               "https://ffmpeg.org/releases/ffmpeg-4.4.tar.xz"
    # GIT_REPOSITORY    "https://git.ffmpeg.org/ffmpeg.git"

    PREFIX            ${CMAKE_SOURCE_DIR}/ffmpeg
    SOURCE_DIR        ${CMAKE_SOURCE_DIR}/ffmpeg
    INSTALL_DIR       ${FFMPEG_BUILD_DIR}/install
    TMP_DIR           ${FFMPEG_BUILD_DIR}/tmp
    STAMP_DIR         ${FFMPEG_BUILD_DIR}/stamp
    DOWNLOAD_DIR      ${FFMPEG_BUILD_DIR}/download
    # BINARY_DIR        ${FFMPEG_BUILD_DIR}/build
    LOG_DIR           ${FFMPEG_BUILD_DIR}/logs

    CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/ffmpeg/${FFMPEG_CONFIGURE_COMMAND}
    BUILD_COMMAND     ${MAKE}
    UPDATE_COMMAND     ""
    INSTALL_COMMAND    ""

    BUILD_IN_SOURCE    ON
    LOG_DOWNLOAD       ON
    LOG_UPDATE         ON
    LOG_CONFIGURE      ON
    LOG_BUILD          ON
    LOG_TEST           ON
    LOG_INSTALL        ON

    # DEPENDS ${BINARY_NAME}
    STEP_TARGETS   build
)
# ExternalProject_Add_StepTargets(FFmpeg build)
    #   CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/ffmpeg  -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}

set(FFMPEG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ffmpeg")
set(FFMPEG_INCLUDE_DIRS ${FFMPEG_INCLUDE_DIR})
set(FFMPEG_LIBRARY
    "${CMAKE_SOURCE_DIR}/ffmpeg/libavutil/libavutil.so"
    "${CMAKE_SOURCE_DIR}/ffmpeg/libavcodec/libavcodec.so"
    "${CMAKE_SOURCE_DIR}/ffmpeg/libavformat/libavformat.so"
    "${CMAKE_SOURCE_DIR}/ffmpeg/libavdevice/libavdevice.so"
    "${CMAKE_SOURCE_DIR}/ffmpeg/libavfilter/libavfilter.so"
    "${CMAKE_SOURCE_DIR}/ffmpeg/libswscale/libswscale.so"
    "${CMAKE_SOURCE_DIR}/ffmpeg/libswresample/libswresample.so"
    "${CMAKE_SOURCE_DIR}/ffmpeg/libpostproc/libpostproc.so"
    "${CMAKE_SOURCE_DIR}/ffmpeg/libavresample/libavresample.so"
)
set(FFMPEG_LIBRARIES ${FFMPEG_LIBRARY})

# This tells cmake to treat those files as system headers, so all their warnings aren't tripping us up
include_directories(SYSTEM ${FFMPEG_INCLUDE_DIR})

set(DEPENDENCIES ${DEPENDENCIES} sphinxbase)


# set(GAME_DEPENDENCY_LIBRARIES
    # ${GAME_DEPENDENCY_LIBRARIES}
    # ${SDL2_LIBRARY}
    # dl
# )