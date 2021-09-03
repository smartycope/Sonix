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

# add_subdirectory(spectogram)
# add_executable(demo main.cpp)

message(STATUS "sndfile include dirs path: ${LIBSNDFILE_INCLUDE_DIRS}")
message(STATUS "sndfile libs path: ${LIBSNDFILE_LIBRARIES}")




set(SndFile_VERSION 1.1.0)
set(SndFile_VERSION_MAJOR 1)
set(SndFile_VERSION_MINOR 1)
set(SndFile_VERSION_PATCH 0)

set (SndFile_WITH_EXTERNAL_LIBS 1)


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was SndFileConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

include (CMakeFindDependencyMacro)

if (SndFile_WITH_EXTERNAL_LIBS AND NOT 1)
	find_dependency (Ogg 1.3)
	find_dependency (Vorbis)
	find_dependency (FLAC)
	find_dependency (Opus)
endif ()

include (${CMAKE_CURRENT_LIST_DIR}/SndFileTargets.cmake)

set_and_check (SndFile_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include") # was ${PACKAGE_PREFIX_DIR}/include
set (SNDFILE_INCLUDE_DIR ${SndFile_INCLUDE_DIR})

set (SndFile_LIBRARY SndFile::sndfile)
set (SNDFILE_LIBRARY SndFile::sndfile)
set (SndFile_LIBRARIES SndFile::sndfile)
set (SNDFILE_LIBRARIES SndFile::sndfile)


check_required_components(SndFile)

set (SNDFILE_FOUND 1)
