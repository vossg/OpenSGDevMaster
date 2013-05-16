CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(OSGOpenExrSrcDir AND OSGZLibSrcDir)

  MESSAGE(STATUS "adding OpenEXR from : ${OSGOpenExrSrcDir}")

  IF(OSGOpenExrSrcDir MATCHES "OpenEXR$")
    ADD_SUBDIRECTORY(Initial)
  ELSE()
    ADD_SUBDIRECTORY(Current)
  ENDIF()

ELSE(OSGOpenExrSrcDir AND OSGZLibSrcDir)
  MESSAGE(STATUS "ignoring OpenEXR")

  SET(OSGOpenExrSrcDir "" CACHE PATH "")
ENDIF(OSGOpenExrSrcDir AND OSGZLibSrcDir)
