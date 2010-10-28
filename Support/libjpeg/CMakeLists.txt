CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGJpegLibSrcDir)

  PROJECT(OSGJpegLib)

  SET(${PROJECT_NAME}SharedTarget osgjpg)
  SET(${PROJECT_NAME}StaticTarget libosgjpg)

  SET(OSG_JPEGLIB_SRCS ${OSGJpegLibSrcDir}/jmemnobs.c

                       ${OSGJpegLibSrcDir}/jcomapi.c 
                       ${OSGJpegLibSrcDir}/jutils.c 
                       ${OSGJpegLibSrcDir}/jerror.c 
                       ${OSGJpegLibSrcDir}/jmemmgr.c

                       ${OSGJpegLibSrcDir}/jcapimin.c 
                       ${OSGJpegLibSrcDir}/jcapistd.c 
                       ${OSGJpegLibSrcDir}/jctrans.c 
                       ${OSGJpegLibSrcDir}/jcparam.c 
                       ${OSGJpegLibSrcDir}/jdatadst.c 
                       ${OSGJpegLibSrcDir}/jcinit.c 
                       ${OSGJpegLibSrcDir}/jcmaster.c 
                       ${OSGJpegLibSrcDir}/jcmarker.c 
                       ${OSGJpegLibSrcDir}/jcmainct.c 
                       ${OSGJpegLibSrcDir}/jcprepct.c
                       ${OSGJpegLibSrcDir}/jccoefct.c 
                       ${OSGJpegLibSrcDir}/jccolor.c 
                       ${OSGJpegLibSrcDir}/jcsample.c 
                       ${OSGJpegLibSrcDir}/jchuff.c 
                       ${OSGJpegLibSrcDir}/jcphuff.c 
                       ${OSGJpegLibSrcDir}/jcdctmgr.c 
                       ${OSGJpegLibSrcDir}/jfdctfst.c 
                       ${OSGJpegLibSrcDir}/jfdctflt.c 
                       ${OSGJpegLibSrcDir}/jfdctint.c

                       ${OSGJpegLibSrcDir}/jdapimin.c 
                       ${OSGJpegLibSrcDir}/jdapistd.c 
                       ${OSGJpegLibSrcDir}/jdtrans.c 
                       ${OSGJpegLibSrcDir}/jdatasrc.c 
                       ${OSGJpegLibSrcDir}/jdmaster.c 
                       ${OSGJpegLibSrcDir}/jdinput.c 
                       ${OSGJpegLibSrcDir}/jdmarker.c 
                       ${OSGJpegLibSrcDir}/jdhuff.c 
                       ${OSGJpegLibSrcDir}/jdphuff.c
                       ${OSGJpegLibSrcDir}/jdmainct.c 
                       ${OSGJpegLibSrcDir}/jdcoefct.c 
                       ${OSGJpegLibSrcDir}/jdpostct.c 
                       ${OSGJpegLibSrcDir}/jddctmgr.c 
                       ${OSGJpegLibSrcDir}/jidctfst.c
                       ${OSGJpegLibSrcDir}/jidctflt.c 
                       ${OSGJpegLibSrcDir}/jidctint.c 
                       ${OSGJpegLibSrcDir}/jidctred.c 
                       ${OSGJpegLibSrcDir}/jdsample.c 
                       ${OSGJpegLibSrcDir}/jdcolor.c 
                       ${OSGJpegLibSrcDir}/jquant1.c 
                       ${OSGJpegLibSrcDir}/jquant2.c 
                       ${OSGJpegLibSrcDir}/jdmerge.c)

  SET(OSG_LIBJPG_HDR ${OSGJpegLibSrcDir}/jpeglib.h 
                     ${OSGJpegLibSrcDir}/jconfig.h
                     ${OSGJpegLibSrcDir}/jmorecfg.h
                     ${OSGJpegLibSrcDir}/jerror.h)

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${PROJECT_SOURCE_DIR}/jmorecfg.h"
                     "${OSGJpegLibSrcDir}/")

  IF(BUILD_STATIC_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_JPEGLIB_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_STATIC_LIBS)

  INSTALL(FILES ${OSG_LIBJPG_HDR}
          DESTINATION include
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  SET(OSG_JPEG_INCLUDE_DIR ${OSGJpegLibSrcDir} CACHE PATH "")
  SET(OSG_JPEG_STATIC_LIBRARY ${${PROJECT_NAME}StaticTarget} CACHE STRING "")
  SET(OSG_JPEG_SHARED_LIBRARY ${${PROJECT_NAME}SharedTarget} CACHE STRING "")

ELSE(OSGJpegLibSrcDir)
  SET(OSGJpegLibSrcDir "" CACHE PATH "")
ENDIF(OSGJpegLibSrcDir)
