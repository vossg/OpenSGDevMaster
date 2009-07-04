CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGZLibSrcDir)

  PROJECT(OSGZLib)

  SET(${PROJECT_NAME}SharedTarget osgzlib)
  SET(${PROJECT_NAME}StaticTarget libosgzlib)

#  SET(${PROJECT_NAME}SharedTargetMini osgminizip)
  SET(${PROJECT_NAME}StaticTargetMini libosgminizip)

  SET(OSG_ZLIB_SRCS ${OSGZLibSrcDir}/adler32.c 
                    ${OSGZLibSrcDir}/compress.c 
                    ${OSGZLibSrcDir}/crc32.c 
                    ${OSGZLibSrcDir}/deflate.c 
                    ${OSGZLibSrcDir}/gzio.c 
                    ${OSGZLibSrcDir}/infback.c 
                    ${OSGZLibSrcDir}/inffast.c 
                    ${OSGZLibSrcDir}/inflate.c 
                    ${OSGZLibSrcDir}/inftrees.c 
                    ${OSGZLibSrcDir}/trees.c 
                    ${OSGZLibSrcDir}/uncompr.c 
                    ${OSGZLibSrcDir}/zutil.c)

  SET(OSG_MINIZIP_SRCS ${OSGZLibSrcDir}/contrib/minizip/zip.c
                       ${OSGZLibSrcDir}/contrib/minizip/unzip.c
                       ${OSGZLibSrcDir}/contrib/minizip/ioapi.c)

  SET(OSG_ZLIB_HDR ${OSGZLibSrcDir}/zlib.h 
                   ${OSGZLibSrcDir}/zconf.h
                   ${OSGZLibSrcDir}/contrib/minizip/zip.h
                   ${OSGZLibSrcDir}/contrib/minizip/unzip.h
                   ${OSGZLibSrcDir}/contrib/minizip/ioapi.h)

  INCLUDE_DIRECTORIES(${OSGZLibSrcDir})

  IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED ${OSG_ZLIB_SRCS})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          DEFINE_SYMBOL ZLIB_DLL   
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)


#    ADD_LIBRARY(${${PROJECT_NAME}SharedTargetMini} SHARED ${OSG_MINIZIP_SRCS})

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetMini} PROPERTIES
#                          DEFINE_SYMBOL ZLIB_DLL   
#                          DEBUG_POSTFIX "D")

#    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTargetMini} PROPERTIES
#                          COMPILE_DEFINITIONS "ZLIB_INTERNAL")

#    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTargetMini} ${${PROJECT_NAME}SharedTarget})

#    INSTALL(TARGETS ${${PROJECT_NAME}SharedTargetMini}
#                CONFIGURATIONS Release Debug
#                RUNTIME DESTINATION bin
#                LIBRARY DESTINATION lib
#                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_ZLIB_SRCS})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)


    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetMini} STATIC ${OSG_MINIZIP_SRCS})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTargetMini} PROPERTIES
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetMini}
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

ELSE(OSGZLibSrcDir)
  SET(OSGZLibSrcDir "" CACHE PATH "")
ENDIF(OSGZLibSrcDir)
