CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(OSGZLibSrcDir)

  PROJECT(OSGZLib)

  SET(${PROJECT_NAME}SharedTarget osgzlib)
  SET(${PROJECT_NAME}StaticTarget libosgzlib)

  IF(EXISTS ${OSGZLibSrcDir}/source)
    SET(OSGZLibSrcDir ${OSGZLibSrcDir}/source CACHE PATH "")
  ENDIF()

  SET(OSG_ZLIB_SRCS ${OSGZLibSrcDir}/adler32.c 
                    ${OSGZLibSrcDir}/compress.c 
                    ${OSGZLibSrcDir}/crc32.c 
                    ${OSGZLibSrcDir}/deflate.c 
                    ${OSGZLibSrcDir}/infback.c 
                    ${OSGZLibSrcDir}/inffast.c 
                    ${OSGZLibSrcDir}/inflate.c 
                    ${OSGZLibSrcDir}/inftrees.c 
                    ${OSGZLibSrcDir}/trees.c 
                    ${OSGZLibSrcDir}/uncompr.c 
                    ${OSGZLibSrcDir}/zutil.c)
  IF(EXISTS ${OSGZLibSrcDir}/gzio.c)
    SET(OSG_ZLIB_SRCS ${OSG_ZLIB_SRCS}
                      ${OSGZLibSrcDir}/gzio.c)
  ELSE()
    SET(OSG_ZLIB_SRCS ${OSG_ZLIB_SRCS}
                      ${OSGZLibSrcDir}/gzclose.c
                      ${OSGZLibSrcDir}/gzlib.c
                      ${OSGZLibSrcDir}/gzread.c
                      ${OSGZLibSrcDir}/gzwrite.c)
  ENDIF()

  SET(OSG_ZLIB_HDR ${OSGZLibSrcDir}/zlib.h 
                   ${OSGZLibSrcDir}/zconf.h)

  INCLUDE_DIRECTORIES(${OSGZLibSrcDir})

  IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED ${OSG_ZLIB_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          DEFINE_SYMBOL ZLIB_DLL   
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)

  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_ZLIB_SRCS})
    
    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)

  ENDIF(BUILD_STATIC_LIBS)

  INSTALL(FILES ${OSG_ZLIB_HDR}
          DESTINATION include
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

  SET(OSG_ZLIB_INCLUDE_DIR ${OSGZLibSrcDir} CACHE PATH "")
  SET(OSG_ZLIB_STATIC_LIBRARY ${${PROJECT_NAME}StaticTarget} CACHE STRING "")
  SET(OSG_ZLIB_SHARED_LIBRARY ${${PROJECT_NAME}SharedTarget} CACHE STRING "")

ELSE(OSGZLibSrcDir)
  SET(OSGZLibSrcDir "" CACHE PATH "")
ENDIF(OSGZLibSrcDir)
