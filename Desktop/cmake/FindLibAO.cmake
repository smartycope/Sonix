
FIND_PATH(LIBAO_INCLUDE_DIR ao.h /usr/include/ao /usr/local/include/ao)

FIND_LIBRARY(LIBAO_LIBRARIES NAMES ao PATH /usr/lib /usr/local/lib)

IF (LIBAO_INCLUDE_DIR AND LIBAO_LIBRARIES)
  SET(LIBAO_FOUND TRUE)
ENDIF (LIBAO_INCLUDE_DIR AND LIBAO_LIBRARIES)

IF (LIBAO_FOUND)
   IF (NOT LIBAO_FIND_QUIETLY)
      MESSAGE(STATUS "Found libao: ${LIBAO_LIBRARIES}")
   ENDIF (NOT LIBAO_FIND_QUIETLY)
ELSE (LIBAO_FOUND)
   IF (LIBAO_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find libao")
   ENDIF (LIBAO_FIND_REQUIRED)
ENDIF (LIBAO_FOUND)

include_directories(${LIBAO_INCLUDE_DIR} ${MPG123_INCLUDE_DIRS})
