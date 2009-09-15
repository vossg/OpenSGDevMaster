
# CMake's ADD_SUBDIRECTORY only looks for CMakeLists.txt, so we include
# the real file here

IF(OSG_BUILD_ACTIVE)
  INCLUDE("CMakeLists.Lib.OSGExGPUVolRT.txt")
ELSE(OSG_BUILD_ACTIVE)

  CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

  PROJECT(OpenSGCustIntEx)

  IF(NOT _OSGINITCACHELOADED 
     AND EXISTS ${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)

      INCLUDE(${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)
      SET(_OSGINITCACHELOADED TRUE CACHE INTERNAL "")

  ENDIF(NOT _OSGINITCACHELOADED AND 
        EXISTS ${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)

  SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${OpenSG_DIR}/share/OpenSG/cmake")

  INCLUDE(ExternalProjectHelper)

  SET(OSG_COMPONENTS OSGBase OSGSystem OSGState OSGGroup OSGDrawable OSGWindow
                     OSGText OSGUtil OSGWindowGLUT)

  IF(UNIX)
    IF(APPLE)
      LIST(APPEND OSG_COMPONENTS OSGWindowCarbon)
    ELSE(APPLE)
      LIST(APPEND OSG_COMPONENTS OSGWindowX)
    ENDIF(APPLE)
  ENDIF(UNIX)

  IF(WIN32)
    LIST(APPEND OSG_COMPONENTS OSGWindowWIN32)
  ENDIF(WIN32)

  OSG_INIT(${OSG_COMPONENTS})

  ##############################################################################
  # MAIN BUILD STEPS
  ##############################################################################

  ## important, must be done here, inside collect it does not work
  SET(OSG_BUILD_ACTIVE TRUE)

  OSG_COLLECT_LIBS()

ENDIF(OSG_BUILD_ACTIVE)
