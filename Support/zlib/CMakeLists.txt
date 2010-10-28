CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGZLibSrcDir)

  PROJECT(OSGZLib)

  SET(${PROJECT_NAME}SharedTarget osgzlib)
  SET(${PROJECT_NAME}StaticTarget libosgzlib)

#  SET(${PROJECT_NAME}SharedTargetMini osgminizip)
  SET(${PROJECT_NAME}StaticTargetMini libosgminizip)

  SET(OSG_ZLIB_SRCS ${OSGZLibSrcDir}/source/adler32.c 
                    ${OSGZLibSrcDir}/source/compress.c 
                    ${OSGZLibSrcDir}/source/crc32.c 
                    ${OSGZLibSrcDir}/source/deflate.c 
                    ${OSGZLibSrcDir}/source/gzio.c 
                    ${OSGZLibSrcDir}/source/infback.c 
                    ${OSGZLibSrcDir}/source/inffast.c 
                    ${OSGZLibSrcDir}/source/inflate.c 
                    ${OSGZLibSrcDir}/source/inftrees.c 
                    ${OSGZLibSrcDir}/source/trees.c 
                    ${OSGZLibSrcDir}/source/uncompr.c 
                    ${OSGZLibSrcDir}/source/zutil.c)

  SET(OSG_MINIZIP_SRCS ${OSGZLibSrcDir}/source/contrib/minizip/zip.c
                       ${OSGZLibSrcDir}/source/contrib/minizip/unzip.c
                       ${OSGZLibSrcDir}/source/contrib/minizip/ioapi.c)

  SET(OSG_ZLIB_HDR ${OSGZLibSrcDir}/source/zlib.h 
                   ${OSGZLibSrcDir}/source/zconf.h
                   ${OSGZLibSrcDir}/source/contrib/minizip/zip.h
                   ${OSGZLibSrcDir}/source/contrib/minizip/unzip.h
                   ${OSGZLibSrcDir}/source/contrib/minizip/ioapi.h)

  INCLUDE_DIRECTORIES(${OSGZLibSrcDir}/source)

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
    
    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)


    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetMini} STATIC ${OSG_MINIZIP_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTargetMini})

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

  SET(OSG_ZLIB_INCLUDE_DIR ${OSGZLibSrcDir}/source CACHE PATH "")
  SET(OSG_ZLIB_STATIC_LIBRARY ${${PROJECT_NAME}StaticTarget} CACHE STRING "")
  SET(OSG_ZLIB_SHARED_LIBRARY ${${PROJECT_NAME}SharedTarget} CACHE STRING "")

ELSE(OSGZLibSrcDir)
  SET(OSGZLibSrcDir "" CACHE PATH "")
ENDIF(OSGZLibSrcDir)
